#include "ThreadPool.h"
#include <mutex>
#include <thread>

namespace lbn {


ThreadPool::ThreadPool(int num)
    : size_(num)
{
    if(num < 1) num = 1;
    for(int i = 0; i < num; ++i) {
        threads_[i] = std::thread([this]() {
        while (!shutdown_.load()) {
            Task task;
            {
                std::unique_lock<std::mutex> lck(mtx_);
                cond_.wait(lck, [this](){return tasks_.empty() || shutdown_.load();});
                if(shutdown_.load() == true) {
                    return;
                }
                task = tasks_.front();
                tasks_.pop_front();
            }
          task();
        }
        });
    }
}

ThreadPool::~ThreadPool() {
    stop();
    cond_.notify_all();
}

template<class Function, class... Args>
std::future<typename std::result_of<Function(Args...)>::type> 
ThreadPool::add(Function&& fcn, Args&&... args) {
    typedef typename std::result_of<Function(Args...)>::type return_type;
    typedef std::packaged_task<return_type()> task;

    auto t = std::make_shared<task>(std::bind(std::forward<Function>(fcn), std::forward<Args>(args)...));
    auto ret = t->get_future();
    {
        std::lock_guard<std::mutex> lg(mtx_);
        if (shutdown_.load(std::memory_order_acquire))
            throw std::runtime_error("thread pool has stopped");
        tasks_.emplace([t]{(*t)(); });
    }
    cond_.notify_one();
    return ret;
}

void ThreadPool::stop() { 
    shutdown_.store(true);
}

} // namespace 
