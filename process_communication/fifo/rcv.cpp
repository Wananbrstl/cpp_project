/* receive */
#include <cstdlib>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define P_FIFO "/tmp/.P_FIFO"

int main (int argc, char *argv[])
{
    char cache[1024];
    int fd;
    fd = access(P_FIFO, F_OK); /* 检测是否存在 */
    if(0==fd) { // exsit 
        execlp("rm", "-f", P_FIFO, NULL);
        printf("success!\n");
    }

    if(mkfifo(P_FIFO, 0777) < 0)  {
        printf("create fifo error!\n");
    }
    fd = open(P_FIFO, O_WRONLY);
    while(1) {
        memset(cache, 0, sizeof(cache));
        if(read(fd, cache, sizeof(cache))) {
            printf("read data : %s\n", cache);
            return 1;
        }
    }
    return 0;
}
