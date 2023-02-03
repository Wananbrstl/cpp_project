#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>

struct Task;
struct Worker;
struct threadPool;

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

//NOTE: Task
struct Task {
    void (*func)(void*);
    void* arg;

    struct Task* next; 
    struct Task* prev;
};

//NOTE: thread pool
struct threadPool {

    struct Worker* workerQ;
    struct Task* taskQ;

    pthread_mutex_t mtx;
    pthread_cond_t cond;
};

//NOTE: worker thread
struct Worker {
    struct Worker *next, *prev;
    struct threadPool* thread_pool;

    int shutdown;
    pthread_t id;
};



//NOTE: every worker thread run
void* thread_task_cycle(void* arg) {
    struct Worker* worker = (struct Worker*)arg;
    while(worker->shutdown) {
        pthread_mutex_lock(&worker->thread_pool->mtx);
        while(worker->thread_pool->taskQ == NULL) {
            pthread_cond_wait(&worker->thread_pool->cond, &worker->thread_pool->mtx);
        }
        
        struct Task* task = worker->thread_pool->taskQ;
        LINK_REMOTE(task, worker->thread_pool->taskQ);
        
        pthread_mutex_unlock(&worker->thread_pool->mtx);
        // work
        printf("[]start work!\n");
        task->func(task->arg);
    }
    return NULL;
}

//NOTE: thread pool start up function 
//      create num worker thread to run `thread_task_cycle`
int thread_pool_startup(struct threadPool* pool, int num) {
    assert(pool != NULL);
    if(num < 1) num = 1;
    int idx = 0;
    for(; idx < num; ++idx) {
        struct Worker* worker = (struct Worker*)malloc(sizeof(struct Worker));
        if(worker == NULL) {
            perror("malloc");
            return -1;
        }
        //TODO: memset的作用？
        memset(worker, 0, sizeof(struct Worker));
        pthread_create(&worker->id, NULL, thread_task_cycle, worker);
        printf("create thread[%ld]!\n", worker->id);
        //TODO: 是否应该加锁?
        LINK_ADD(worker, pool->workerQ);
        //TODO: usleep的作用?
        // usleep(1); // chirden first
    }
    return 1;
}

//NOTE: push a task to a thread pool
void task_push(struct threadPool* thrdpool, struct Task* node){
    pthread_mutex_lock(&thrdpool->mtx);
    LINK_ADD(node, thrdpool->taskQ);
    pthread_cond_signal(&thrdpool->cond);
    pthread_mutex_unlock(&thrdpool->mtx);
}

void task1() {
    while(1) {
        printf("this is task1\n");
        usleep(100);
    }
}
void task2(void* argc) {
    int* arg = (int*)argc;
    while(1) {
        printf("this is task2, and argc is %d!\n", *arg);
        usleep(100);
    }
}

int main (int argc, char *argv[])
{
    int num = 2;
    struct threadPool* thrd_pool = (struct threadPool*)malloc(sizeof(struct threadPool));

    struct Task* t1 = (struct Task*)malloc(sizeof(struct Task));
    t1->func = task1;
    t1->arg = NULL;

    struct Task* t2 = (struct Task*)malloc(sizeof(struct Task));
    t2->func = task2;
    t2->arg = &num;

    thread_pool_startup(thrd_pool, 4);
    task_push(thrd_pool, t1);
    task_push(thrd_pool, t2);
    while(1);
    return 0;
}
