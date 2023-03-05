#include <cstdio>
#include <iostream>
#include <cmath>

typedef long long LL;

const int N = 100010;

using namespace std;


struct Node {
    int l, r;
    LL sum, add;
} tr[4 * N];

int w[N];

void pushup(int u){
    tr[u].sum = tr[u<<1].sum +tr[u<<1 |1].sum;
}

void pushdown(int u){
    if(!tr[u].add) return;
    tr[u << 1].add += tr[u].add, tr[u << 1].sum += (tr[u << 1].r - tr[u << 1].l + 1) * tr[u].add;
    tr[u << 1 | 1].add += tr[u].add, tr[u << 1 | 1].sum += (tr[u << 1 | 1].r - tr[u << 1 | 1].l + 1) * tr[u].add;
    tr[u].add = 0;
}

void build(int u, int l, int r) {
    if(l == r) tr[u] = {l, r, w[l], 0};
    else {
        tr[u].l = l, tr[u].r = r;
        int mid = l + r  >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    // printf("%d %d %d\n", u, l, r);
}

void modify(int u, int l, int r, int d) {
    if(tr[u].l >= l && tr[u].r <= r) {
        tr[u].sum += (LL)(tr[u].r - tr[u].l + 1) * d;
        tr[u].add += d;
    }else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if(l <= mid) modify(u << 1, l, r, d);
        if(r > mid) modify(u << 1 | 1, l, r, d);
        pushup(u);
    }
}

LL query(int u, int l, int r){ 
    if(tr[u].l >= l && tr[u].r <= r) return tr[u].sum;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    LL res = 0;
    if(l <= mid) res += query(u << 1, l, r);
    if(r > mid) res += query(u << 1 | 1, l, r);
    return res;
}


int main (int argc, char *argv[])
{
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) cin >> w[i];
    build(1, 1, n);

    char op;
    int l, r, d;
    while (m--) {
        cin >> op >> l >> r;
        if(op == 'Q') {
            printf("%lld\n", query(1, l, r));
        } else {
            cin >> d;
            modify(1, l, r, d);
        }
    }
    return 0;
}
