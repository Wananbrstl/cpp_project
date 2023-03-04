#include <cstdio>
#include <iostream>
#include <vector>

#define N 500020
#define lchild(u) u<<1
#define rchild(u) u<<1|1

using namespace std;

struct Node {
    int l, r;
    int lmax, rmax, sum, mx;
} tr[N * 4];
int w[N];

// void pushUp(int u) {
//     tr[u].sum = tr[lchild(u)].sum + tr[rchild(u)].sum;
//     tr[u].lmax = max(tr[lchild(u)].lmax, tr[lchild(u)].sum + tr[rchild(u)].lmax);
//     tr[u].rmax = max(tr[rchild(u)].rmax, tr[rchild(u)].sum + tr[lchild(u)].rmax);
//     tr[u].mx = max(tr[lchild(u)].mx, max(tr[rchild(u)].mx, tr[lchild(u)].rmax + tr[rchild(u)].lmax));
// }

void pushUp(Node& u, Node& l, Node& r) {
    u.sum = l.sum + r.sum;
    u.mx = max(l.rmax + r.lmax, max(l.mx, r.mx));
    u.lmax = max(r.lmax + l.sum, l.lmax);
    u.rmax = max(l.rmax + r.sum, r.rmax);
}

void build(int u, int l, int r){
    tr[u].l = l, tr[u].r = r;
    if(l == r) {
        tr[u].sum = w[l], tr[u].lmax = w[l], tr[u].rmax = w[r], tr[u].mx = w[l];
    } else{ 
        int mid = (l + r) >> 1;
        build(lchild(u), l, mid), build(rchild(u), mid+1,r);
        pushUp(tr[u], tr[lchild(u)], tr[rchild(u)]);
    }
}

void modify(int u, int x, int v){
    if(tr[u].l == x && tr[u].r == x) {
        tr[u].sum = v, tr[u].lmax = v, tr[u].rmax = v, tr[u].mx = v;
    } else {
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(mid < x) modify(rchild(u), x, v);
        else modify(lchild(u), x, v);
        pushUp(tr[u], tr[lchild(u)], tr[rchild(u)]);
    }
}

Node query(int u, int l, int r){
    if(tr[u].l >= l && r >= tr[u].r) return tr[u];
    int mid = (tr[u].l + tr[u].r) >> 1;
    if(r <= mid) return query(lchild(u), l, r);
    else if(l > mid) return query(rchild(u), l, r);
    else {
        auto left = query(lchild(u), l, r);
        auto right = query(rchild(u), l, r);
        Node res;
        pushUp(res, left, right);
        return res;
    }
}

int n, m;
int main (int argc, char *argv[])
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i) scanf("%d", &w[i+1]);

    build(1, 1, n);
    for(int i = 0; i < 4 * n; ++i) {
        printf("%d ", tr[i].sum);
    }
    cout << endl;
    int op, x, y;
    while (m--) {
        scanf("%d%d%d", &op, &x, &y);
        if(op == 1) {// query
            if(x > y) swap(x, y);
            printf("%d\n", query(1, x, y).mx);
        } else {
            modify(1, x, y);
        }
    }
    return 0;
}
