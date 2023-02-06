#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <fcntl.h>

#include "mymsg.h"

#define  ERROR(m) do \
{                    \
    perror(m);       \
    exit(-1);        \
} while(0);          

int main (int argc, char *argv[])
{
    key_t key;
    key = ftok(PATH, 0);
    int fd = open(PATH, O_CREAT|O_RDONLY);
    int ok = msgget(key, 0);
    if(ok < 0) {
        ERROR("msgget");
    }
    struct msgbuffer buf;
    Data data;
    data.age = 10;
    sprintf(data.name, "name-%03d", rand() % 1000);
    buf.mtype = MYTYPE;
    buf.mdata = data;
    msgsnd(key, , size_t msgsz, int msgflg);
    return 0;
}
