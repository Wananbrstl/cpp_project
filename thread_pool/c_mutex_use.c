// NOTE: this is a example for productor-comsummer model with c 
//       key1: 有哪些是有顺序的!
//       key2: 判断条件！
#include <stdint.h>
#include <pthread.h>
#include <stdio.h>

#define BUFFER_SIZE 1
#define PRODUCTOR_NUM 4
#define COMSUMMER_NUM 1

int buffer[BUFFER_SIZE];
pthread_t comsummer_thrds[COMSUMMER_NUM];
pthread_t productor_thrds[PRODUCTOR_NUM];
int current_idx = 0;
pthread_mutex_t mtx  = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full  = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

void* productor(void* arg){
    while(1) {
        pthread_mutex_lock(&mtx);
        while(current_idx == BUFFER_SIZE) {
            pthread_cond_wait(&empty, &mtx);
        }
        current_idx++;
        printf("[productor], current id = %d\n", current_idx);
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

void* comsummer(void* argc) {
    while (1) {
        pthread_mutex_lock(&mtx);
        while(current_idx == 0) {
            pthread_cond_wait(&full, &mtx);
        }
        current_idx--;
        printf("[comsummer], current id = %d\n", current_idx);
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main (int argc, char *argv[])
{
    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    for(int i = 0; i < PRODUCTOR_NUM; ++i) {
        pthread_create(&productor_thrds[i],NULL, productor, NULL);
    }
    for(int i = 0; i < COMSUMMER_NUM; ++i) {
        pthread_create(&comsummer_thrds[i],NULL, comsummer, NULL);
    }

    for(int i = 0; i < PRODUCTOR_NUM; ++i) {
        pthread_join(productor_thrds[i], NULL);
    }
    for(int i = 0; i < COMSUMMER_NUM; ++i) {
        pthread_join(comsummer_thrds[i], NULL);
    }
    return 0;
}
