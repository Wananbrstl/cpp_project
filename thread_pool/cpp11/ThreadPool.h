#pragma once

#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <deque>
#include <atomic>
#include <functional>
#include <future>
#include <utility>

namespace lbn {

class ThreadPool {
public:
    typedef std::function<void()>  Task;

    explicit ThreadPool(int num = 10);
    ~ThreadPool();

    template<class Function, class... Args>
    std::future<typename std::result_of<Function(Args...)>::type> 
    add(Function&&, Args&&...);

    void stop();

private:
    ThreadPool(const ThreadPool& other) = delete;
    ThreadPool& operator=(const ThreadPool& other) = delete;

    int size_;
    std::atomic<bool> shutdown_;
    std::mutex mtx_;
    std::condition_variable cond_;
    std::vector<std::thread> threads_;
    std::deque<Task> tasks_;
};

} // namespace 
