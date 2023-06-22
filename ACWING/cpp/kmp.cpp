#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10, M = 1e6 + 10;

int n, m, ne[N];
char s[M], p[N];

// version 0  下标从0开始
int main (int argc, char *argv[])
{
    cin >> n >> (p + 1) >> m >> (s + 1);
    ne[0] = -1;
    for(int i = 1, j = -1; i < n; ++i) {
        while(j >= 0 && p[i] != p[j + 1]) j = ne[j];
        if(p[i] == p[j + 1]) j++;
        ne[j] = j;
    }
    for(int i = 0, j = -1; i < m; ++i) {
        while(j != -1 && s[i] != p[j + 1]) j = ne[j];
        if(s[i] == p[j + 1]) j++;
        if(j == n - 1) {
            printf("%d ", i - n + 1);
            j = ne[j];
        }
    }
    return 0;
}
// version 1: 下标从1开始
// int main (int argc, char *argv[])
// {
//     cin >> n >> (p + 1) >> m >> (s + 1) ;   
//     for(int i = 2, j = 0; i <= n; ++i) {
//         while (j && p[i] != p[j + 1])  {
//             j = ne[j];
//             printf("%d ==> %d\n", j, ne[j]);
//         }
//         if(p[i] == p[j + 1]) {
//             j++;
//             printf("j++, j = %d\n", j);
//         }
//         ne[i] = j;
//         printf("ne[%d] = %d\n",i,ne[i]);
//     }
//     for(int i = 1, j = 0; i <= m; ++i) {
//         while(j && s[i] != p[j + 1]) j = ne[j];
//         if(s[i] == p[j + 1]) j++;
//         if(j == n) {
//             printf("%d\n", i - n);
//             j = ne[j];
//         }
//     }
//     return 0;
// }
