#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

long fileSize(FILE* stream) {
    long curPos, len;
    curPos = ftell(stream);
    fseek(stream, 0L, SEEK_END);
    len = ftell(stream);
    fseek(stream, curPos, SEEK_SET);
    return len;
}

int main (int argc, char *argv[])
{
    FILE* fstream = fopen(argv[1], "rw+");
    if(NULL == fstream) {
        printf("not exist!\n");
        return -1;
    }
    // fseek(fstream, 0L, SEEK_END);
    fprintf(fstream, "FUCK!\n");
    fclose(fstream);
    return 0;
}
