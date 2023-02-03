#include "ThreadPool.h"
#include <cstdio>
#include <pthread.h>
#include <assert.h>

namespace lbn {
// public
ThreadPool::ThreadPool(int thread_num) {
    shutdown_ = false;
    thread_num_ = thread_num;
    createThreads();
}

// public
int ThreadPool::size() {
    pthread_mutex_lock(&mtx_);
    int sz = taskQue_.size();
    pthread_mutex_unlock(&mtx_);
    return sz;
}

// public
ThreadPool::~ThreadPool() {
    stop();
}

// public
size_t ThreadPool::addTask(const Task& task) {
    pthread_mutex_lock(&mtx_);
    taskQue_.push_back(task);
    int size = taskQue_.size();
    pthread_cond_signal(&cond_);
    pthread_mutex_unlock(&mtx_);
    return size;
}

// public
void ThreadPool::stop() {
    if(shutdown_) {
        return;
    }
    shutdown_ = true;
    pthread_cond_broadcast(&cond_);
    for(int i = 0; i < thread_num_; ++i) {
        pthread_join(threads_[i], NULL);
    }
    free(threads_);
    threads_ = NULL;

    pthread_mutex_destroy(&mtx_);
    pthread_cond_destroy(&cond_);
}

// public
ThreadPool::Task ThreadPool::take() {
    Task task = NULL;
    pthread_mutex_lock(&mtx_);
    while(taskQue_.empty() && !shutdown_) {
       pthread_cond_wait(&cond_, &mtx_);
    }
    if(shutdown_) {
        pthread_mutex_unlock(&mtx_);
        return task;
    }
    assert(!taskQue_.empty());
    task = taskQue_.front();
    taskQue_.pop_front();
    pthread_mutex_unlock(&mtx_);
    return task;
}

// private
int ThreadPool::createThreads() {
    pthread_cond_init(&cond_, NULL);
    pthread_mutex_init(&mtx_, NULL);
    threads_ = (pthread_t*)malloc(sizeof(pthread_t) * thread_num_);
    for(int i = 0; i < thread_num_; ++i) {
        pthread_create(&threads_[i], NULL, threadFunc, this);
    }
    return 0;
}

// private
void* ThreadPool::threadFunc(void* arg) {
    pthread_t tid = pthread_self();
    ThreadPool* pool = static_cast<ThreadPool*>(arg);
    while(!pool->shutdown_) {
        ThreadPool::Task task = pool->take();
        if(!task) {
            printf("thread %lu will eixt!\n", tid);
            break;
        }

        assert(task);
        task();
    }
    return 0;
}

// // private
// ThreadPool&  ThreadPool::operator=(const ThreadPool&) {
//     
// }
//
// // private
// ThreadPool::ThreadPool(const ThreadPool&) {
//
// }
} // namespace
