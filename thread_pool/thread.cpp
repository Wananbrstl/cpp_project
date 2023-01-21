/* 
    该文件展示的是 生产者-消费者模式 的工作模式
*/
#include <condition_variable>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <thread>
#include <iostream>
#include <mutex>
#include <atomic>

#define COMSUMMER 2
#define PRODUCTER 20
#define MAX_SIZE  20

std::queue<int> q; /* NOTE: 由于多个线程会取队列中的数据,所以需要进行同步以及临界区保护 */
std::mutex mtx;
std::condition_variable cv;

void comsumer() {
    while(true) {
        std::this_thread::sleep_for(std::chrono::duration<double>(0.5));
        std::unique_lock<std::mutex> lck(mtx);
        while(q.empty()) cv.wait(lck);
        std::cout << std::this_thread::get_id() << " comsumer:\t" << q.front() << std::endl;
        q.pop();
        cv.notify_all();
    }
}

void product() {
    while(true) {
        std::this_thread::sleep_for(std::chrono::duration<double>(0.5));
        std::unique_lock<std::mutex>  lck(mtx); 
        while(q.size() == MAX_SIZE) cv.wait(lck);
        int data = rand() % 100;
        q.push(data);
        std::cout << std::this_thread::get_id() << " product:\t" << q.front() << std::endl;
        cv.notify_all();
    }
}

int main (int argc, char *argv[])
{
    std::thread com[COMSUMMER];
    std::thread pro[PRODUCTER];
    for(int i = 0; i < COMSUMMER; ++i) {
        com[i] = std::thread(comsumer);
    }
    for(int i = 0; i < PRODUCTER; ++i) {
        pro[i] = std::thread(product);
    }
    for(int i = 0; i < COMSUMMER; ++i) {
        com[i].join();
    }
    for(int i = 0; i < PRODUCTER; ++i) {
        pro[i].join();
    }
    
    return 0;
}
