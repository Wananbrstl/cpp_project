#include <bits/stdc++.h>
#include <cstdio>

#define SHOW(cond) do{std::cout << (cond ? "YES" : "NO") << std::endl;}while(0)

int main (int argc, char *argv[])
{
    printf("test xor : \n");
    SHOW(1 ^ 1);
    SHOW(1 ^ 0);
    SHOW(1 ^ -1);
    SHOW(0 ^ 1);
    SHOW(0 ^ 0);
    SHOW(0 ^ -1);
    SHOW(-1 ^ 1);
    SHOW(-1 ^ 0);
    SHOW(-1 ^ -1);
    return 0;
}
