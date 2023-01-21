#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

namespace lbn{
using callback = void (*)(void*);

/* the task */
struct Task {
    callback func;
    void* arg;

    Task() : 
        func(nullptr), arg(nullptr){}

    Task(callback _func, void* _arg) :
        func(_func), arg(_arg) {}
};

/* the task queue */
class TaskQueue {
public:
    TaskQueue();
    ~TaskQueue();

    void addTask(const Task& _task);
    void addTask(callback _cb, void* _arg);
    Task takeTask();
    inline int taskNum() const {return que_.size();}

private:
    std::queue<Task> que_;   
    std::mutex tsk_que_mtx_;
};

/* thread pool */
class ThreadPool {
public:
    ThreadPool();
    ThreadPool(int _min, int _max); 
    ~ThreadPool();

    void addTask(const Task& _tsk);
    int getBusyNum();
    int getLiveNum();

private:
    static void work(void* _arg);
    static void manager(void *_arg);
    void ThreadExit();

private:
    std::mutex trd_pool_mtx_;               // thread pool data mutex
    std::condition_variable trd_pool_cv_;   // thread pool condition variable
     
    std::thread* wrk_trd_;                  // work thread
    std::thread mnger_trd_;                 // manager pool

    TaskQueue *tsk_que_;                    // task queue
    int busy_num_;                          // current thread pool busy number 
    int alive_num_;                         // current thread pool alive number 
    int min_num_;                           // thread pool maximum number of thread
    int max_num_;                           // thread pool minimum number of thread
    int exit_num_;                          // thread pool exit number of thread
    bool shutdown_;                         // is shutdown?
};
} // namespace lbn
#endif // THREAD_POOL_H_
