#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> Point;
typedef long long LL;

const int N = 1010;

int n;
Point l[N], r[N];
Point q[N];

LL range_area(int a, int b) {
    LL  res = 0;
    int cnt = 0;
    for(int i = 0; i < n; ++i) {
       if(l[i].x <= a && r[i].x >= b)  {
            q[cnt++] = {l[i].y, r[i].y};
        }
    }
    if(cnt == 0) return 0;
    sort(q, q + cnt);
    int st = q[0].x, ed = q[0].y;
    for(int i = 1; i < cnt; ++i) {
        if(q[i].x <= ed) ed = max(q[i].y, ed);
        else {
            res += (ed - st);
            st = q[i].x, ed = q[i].y;
        }
    }
    res += (ed - st);
    return res * (b - a);
}

int main (int argc, char *argv[])
{
    scanf("%d", &n);   
    vector<int> xs;
    for(int i = 0; i < n; ++i) {
        scanf("%d%d%d%d", &l[i].x, &l[i].y, &r[i].x, &r[i].y);
        xs.push_back(l[i].x);
        xs.push_back(r[i].x);
    }

    sort(xs.begin(), xs.end());
    LL res = 0;
    for(int i = 0; i+1< (int)xs.size(); ++i) {
        if(xs[i] == xs[i+1]) continue;
        res += range_area(xs[i], xs[i+1]);
    }
    printf("%lld\n", res);
    return 0;
}
