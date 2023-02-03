#include "ThreadPool.h"
#include <cstdio>
#include <functional>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


class MyTask {
public:
    MyTask(){}

    int run(int i, const char* p) {
        printf("thread[%lu] : (%d, %s)\n", pthread_self(), i, p);
        sleep(1);
        return 0;
    }
};

int main (int argc, char *argv[])
{
    lbn::ThreadPool threadPool(10);
    MyTask taskObj[20];

    for(int i = 0; i < 20; ++i) {
        threadPool.addTask(std::bind(&MyTask::run, &taskObj[i], i, "hello world!")); 
    }
    while (1) {
        printf("there are still %d tasks need to process!\n", threadPool.size());
        if(threadPool.size() == 0) {
            threadPool.stop();
            printf("Now I Will exit from main!\n");
            exit(0);
        }
        sleep(2);
    }

    return 0;
}
