#include <cstdio>
#include <ios>
#include <iostream>
#include <fstream>

int main (int argc, char *argv[])
{
    std::ifstream in("test.txt", std::ios::binary);
#ifdef READ_BY_SEEK
    long len = 0L;
    in.seekg(0L, std::ios_base::end);
    len = in.tellg();
    in.seekg(0L, std::ios_base::beg);
    char* buffer = new char[len];
    in.read(buffer, len);
    printf("%s", buffer);
    delete[] buffer;
#endif
// #ifdef READ_BY_LINE
    int size = 256;
    char buffer[256] = {0};
    while(!in.eof()){
        in.getline(buffer, 256);
        printf("%s", buffer);
        std::cout << "current pos is " << in.tellg() << std::endl;
    }
// #endif
    in.close();
    return 0;
}
