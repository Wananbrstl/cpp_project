#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


#include <stdio.h>

/* NOTE: open() 函数是linux下特有的函数，Windows下没有，
        fopen() 函数是c语言标准函数，跨平台的*/
int main (int argc, char *argv[])
{
    // int fd = open("test.txt", O_RDWR  | O_CREAT);
    // char buffer[14] = "Hello World!\n";
    // write(fd, buffer, 14);
    // lseek(fd, 10, SEEK_END);
    // write(fd, ".", 1);
    // close(fd);
    FILE* file = fopen("test.txt", "rw");
    printf("file mode is : %d\n",file->_mode);
    if(file == NULL) {
        printf("the file is not exsit\n");
        return -1;
    }

    printf("the offset is %ld\n", file->_offset);
    fclose(file);
    return 0;
}
