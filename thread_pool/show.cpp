#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#define THRD_NUM 3
#define LOOP_NUM 100

using namespace std;

mutex mtx;
condition_variable cv;
int flag = 0;
thread trds[THRD_NUM];


void show(int id) {
    for(int i = 0; i < LOOP_NUM; ++ i) {
        unique_lock<mutex> lk(mtx);
        while(flag != id) {
            cv.wait(lk); 
        }
        cout << char('A' + id) << "  ";
        flag  = (flag + 1) % 3;
        cv.notify_all();
    }
		// cv.wait(lk, [=]() {
		// 	return id == flag;
		// 	});
		// cout << (char)('A' + id) << " ";
		// flag = (flag + 1) % 3;
		// cv.notify_all();
    // }
}

int main (int argc, char *argv[])
{
    cout << "starting ..." << endl;
    for(int i = 0; i < THRD_NUM; ++i) {
        trds[i] = thread(show, i);
    }
    cout << "..." << endl;
    for(int i = 0; i < THRD_NUM; ++i) {
        trds[i].join();
    }
    cout << "done!\n";
    return 0;
}
