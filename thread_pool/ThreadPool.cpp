#include "ThreadPool.h" 
#include <atomic>
#include <string.h>
#include <iostream>

namespace lbn{
/*------------------------------------------------------------------------------------*/
TaskQueue::TaskQueue() {
}

TaskQueue::~TaskQueue() {
}

void TaskQueue::addTask(const Task& _task) {
    tsk_que_mtx_.lock();
    que_.push(_task);
    tsk_que_mtx_.unlock();
}

void TaskQueue::addTask(callback _cb, void* _arg) {
    addTask(Task(_cb, _arg));
}

Task TaskQueue::takeTask() {
    Task tsk;
    tsk_que_mtx_.lock();
    if(que_.size()) {
        tsk = que_.front();
        que_.pop();
    }
    tsk_que_mtx_.unlock();
    return tsk;
}

/*------------------------------------------------------------------------------------*/
ThreadPool::ThreadPool() {
    
}

ThreadPool::ThreadPool(int _min, int _max) {
    tsk_que_ = new TaskQueue;
    max_num_ = _max;
    min_num_ = _min;
    alive_num_ = _min;
    busy_num_ = 0;
    exit_num_ = 0;
    shutdown_  = false;

    wrk_trd_ = new std::thread[_max];
    memset(wrk_trd_, 0, sizeof(std::thread) * _max); 
    
    for(int i = 0; i < _min; ++i) {
        wrk_trd_[i] = std::thread(work); 
        // std::cout <<  i+1 << " thread's id is " << wrk_trd_[i].
    }
    mnger_trd_ = std::thread(manager);
}

ThreadPool::~ThreadPool() {
    if(wrk_trd_ != nullptr) delete[] wrk_trd_;
    wrk_trd_ = nullptr;
    if(tsk_que_ != nullptr) delete tsk_que_;
    tsk_que_ = nullptr;
}

void ThreadPool::addTask(const Task& _tsk) {
    trd_pool_mtx_.lock();
    tsk_que_->addTask(_tsk);
    trd_pool_mtx_.unlock();
}

int ThreadPool::getBusyNum(){ 
    int res = 0;
    trd_pool_mtx_.lock();
    res = busy_num_;
    trd_pool_mtx_.unlock();
    return res;
}   

int ThreadPool::getLiveNum() {
    int res = 0;
    trd_pool_mtx_.lock();
    res = alive_num_;
    trd_pool_mtx_.unlock();
    return res;
}   

void ThreadPool::work(void* _arg) {

}

void ThreadPool::manager(void *_arg) {

}

void ThreadPool::ThreadExit() {

}


/*------------------------------------------------------------------------------------*/

} //namespace std;
