#pragma once
#include <pthread.h>
#include <functional>
#include <deque>

namespace lbn {
class ThreadPool {
public:
    typedef std::function<void()> Task;

    ThreadPool(int thread_num = 10);
    ~ThreadPool();

    size_t addTask(const Task& task);
    int size();
    void stop();
    Task take();

private:
    int createThreads();
    static void* threadFunc(void* threadData);

    ThreadPool& operator=(const ThreadPool&);
    ThreadPool(const ThreadPool&);

    volatile bool   shutdown_;
    int             thread_num_;
    pthread_t*      threads_;
    
    std::deque<Task> taskQue_;
    pthread_mutex_t  mtx_;
    pthread_cond_t   cond_;
};

} // namespace 
