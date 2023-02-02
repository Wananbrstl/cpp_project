#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <memory.h>

#define LINK_ADD(item, list)                \
    do{                                     \
        item->prev = NULL;                  \
        item->next = list;                  \
        if(list != NULL) list->prev = item; \
        list = item;                        \
} while(0)

#define LINK_REMOTE(item, list)                      \
    do{                                              \
        if(item->prev) item->prev->next = item->next;\
        if(item->next) item->next->prev = item->prev;\
        if(list == item) list = item->next;          \
        item->next = item->prev = NULL;              \
} while(0)

typedef struct Task Task;
typedef struct Worker Worker;
typedef struct threadPool threadPool;

//NOTE: Task
typedef struct {
    void (*func)(void*);
    void* arg;

    Task* next; 
    Task* prev;
} Task;

//NOTE: worker thread
typedef struct {
    Worker *next, *prev;

    bool shutdown;
    pthread_t id;
    threadPool* thread_pool;

    Worker() {
        next = prev = thread_pool = NULL;
        shutdown = false;
    }

} Worker;

//NOTE: thread pool
typedef struct {

    Worker* workerQ;
    Task* taskQ;

    pthread_mutex_t mtx;
    pthread_cond_t cond;
} threadPool;


//NOTE: every worker thread run
void thread_task_cycle(void* arg) {
    Worker* worker = (Worker*)arg;
    while(worker->shutdown) {
        pthread_mutex_lock(&worker->thread_pool->mtx);
        while(worker->thread_pool->tastQ == NULL) {
            pthread_cond_wait(&worker->thread_pool->cond, &worker->thread_pool->mtx);
        }
        
        Task* task = worker->thread_pool->taskQ;
        LINK_REMOTE(task, worker->thread_pool->taskQ);
        
        pthread_mutex_unlock(&worker->thread_pool->mtx);
        // work
        task->func(task->arg);
    }
}

//NOTE: thread pool start up function 
//      create num worker thread to run `thread_task_cycle`
int thread_pool_startup(threadPool* pool, int num) {
    assert(pool != NULL);
    if(num < 1) num = 1;
    int idx = 0;
    for(; idx < num; ++idx) {
        Worker* worker = (Worker*)malloc(sizeof(Worker));
        if(worker == NULL) {
            perror("malloc");
            return -1;
        }
        //TODO: memset的作用？
        memset(worker, 0, sizeof(Worker));
        pthread_create(&worker->id, NULL, thread_task_cycle, worker);
        //TODO: 是否应该加锁?
        LINK_ADD(worker, pool->workerQ);
        //TODO: usleep的作用?
        usleep(1); // chirden first
    }
    return 1;
}

//NOTE: push a task to a thread pool
void task_push(threadPool* thrdpool, Task* node){
    pthread_mutex_lock(&thrdpool->mtx);
    LINK_ADD(node, thrdpool->taskQ);
    pthread_cond_signal(&thrdpool->cond);
    pthread_mutex_unlock(&thrdpool->mtx);
}
