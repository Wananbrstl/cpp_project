#ifndef MSG__
#define MSG__

#include <sys/types.h>

#define PATH "./.msg"
#define MYTYPE 1

typedef struct  {
    int age;
    char name[64];
} Data;

struct msgbuffer {
    long mtype;
    Data mdata;
};

#endif
