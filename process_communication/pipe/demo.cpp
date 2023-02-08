#include <cwchar>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


int main (int argc, char *argv[])
{
    pid_t pid;
    /*
     *  fd[0] --- in 
     *  fd[1] --- out
     */ 
    int fd[2];
    if(pipe(fd) == -1) {
        perror("pipe");
        return 1;
    } 
    pid = fork();
    if(pid == -1) {
        perror("fork");
        return 1;
    } else if(pid == 0) { // 子进程
        close(fd[1]);
        char buf[1024];
        printf("child pid : %d\n", getpid());
        read(fd[0], buf, sizeof(buf));
        write(STDOUT_FILENO, buf, sizeof(buf));
    } else { // 父进程  
        sleep(1);
        close(fd[0]);
        char buf[1024] = "hello world!\n";
        printf("parent pid : %d\n", getpid());
        snprintf(buf, sizeof(buf), "send data : name-%3d\n", rand() % 1000);
        write(fd[1], buf, sizeof(buf));
        wait(NULL);
    }
    printf("done!\n");
    return 0;
}
