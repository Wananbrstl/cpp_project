#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#define P_FIFO "/tmp/.P_FIFO"

using namespace std;
int main(int argc, char** argv) {
    // if(argc != 2) {
    //     printf("input the data!\n");
    //     return 1;
    // }
    int fd = open(P_FIFO, O_RDONLY);
    if(0 == fd) {
        printf("the file is not exsit!\n");
        return 1;
    }
    char buf[12] = "hello world";
    write(fd, buf, sizeof(buf));
    close(fd);
    return 0;
}
