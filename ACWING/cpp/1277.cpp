#include <cstdio>
#include <iostream>
#include <cstring>


#define lchild(u) u << 1
#define rchild(u) u << 1 | 1

using namespace std;

const int N = 100010;

typedef long long LL ;
struct Node {
    int l, r;
    int sum, add, mul;
}tr[N * 4];

int nums[N], P;

void pushup(int u){
    tr[u].sum = (tr[lchild(u)].sum + tr[rchild(u)].sum) % P;
}
void eval(Node &t, int add, int mul)
{
    t.sum = ((LL)t.sum * mul + (LL)(t.r - t.l + 1) * add) % P;
    t.mul = (LL)t.mul * mul % P;
    t.add = ((LL)t.add * mul + add) % P;
}

void pushdown(int u)
{
    eval(tr[u << 1], tr[u].add, tr[u].mul);
    eval(tr[u << 1 | 1], tr[u].add, tr[u].mul);
    tr[u].add = 0, tr[u].mul = 1;
}

// void pushdown(int u){
//     tr[lchild(u)].add += tr[u].mul * tr[u].add + tr[u].add;
//     tr[lchild(u)].mul += tr[u].mul;
//     tr[rchild(u)].add += tr[u].mul * tr[u].add + tr[u].add;
//     tr[rchild(u)].mul += tr[u].mul;
// }

void build(int u, int l, int r){
    if(l == r) {
        tr[u] = {l, r, nums[l], 0, 1};
    } else {
        tr[u].l = l, tr[u].r = r;
        tr[u].mul = 1;
        int mid = l + r >> 1;
        build(lchild(u), l, mid);
        build(rchild(u), mid+1, r);
        pushup(u);
    }
}

int query(int u, int l, int r){
    if(tr[u].l >= l && tr[u].r <= r) return tr[u].sum % P;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    int res = 0;
    if(l <= mid) res = query(lchild(u), l, r) % P;
    if(r > mid) res = (res + query(rchild(u), l, r)) % P;
    return res;
}

void modify(int u, int l, int r, int add, int mul) {
    if(tr[u].l >= l && tr[u].r <= r) {
        eval(tr[u], add, mul);
    } else {
        pushdown(u);
        int mid = tr[u].r + tr[u].l >> 1;
        if ( l <= mid) modify(lchild(u), l, r, add, mul);
        if ( r > mid) modify(rchild(u), l, r, add, mul);
        pushup(u);
    }
}

int n, m;
int main (int argc, char *argv[])
{
    cin >> n >> P;
    for(int i = 1; i <= n; ++i) cin >> nums[i];
    build(1, 1, n);
    cin >> m;
    int op, l, r, add, mul;
    while (m--) {
        cin >> op >> l >> r;
        if(op == 1) {
            cin >> mul;
            modify(1, l, r, 0, mul);
        } else if(op == 2) {
            cin >> add;
            modify(1, l, r, add, 1);
        } else {
            printf("%d\n", query(1, l, r));
        }
    }
    return 0;
}

// void debug() {
//     printf("====================================\n");
//     printf("u\tl\tr\tsum\tadd\tmul\n");
//     for(int i = 1; i < 4 *  n; ++i) {
//         printf("%d\t%d\t%d\t%lld\t%lld\t%lld\n", i, tr[i].l, tr[i].r, tr[i].sum, tr[i].add, tr[i].mul);
//     }
//     printf("====================================\n");
// }
// int main()
// {
//     scanf("%d%d", &n, &P);
//     for (int i = 1; i <= n; i ++ ) scanf("%d", &nums[i]);
//     build(1, 1, n);
//     debug();
//     scanf("%d", &m);
//     while (m -- )
//     {
//         int t, l, r, d;
//         scanf("%d%d%d", &t, &l, &r);
//         if (t == 1)
//         {
//             scanf("%d", &d);
//             modify(1, l, r, 0, d);
//         }
//         else if (t == 2)
//         {
//             scanf("%d", &d);
//             modify(1, l, r, d, 1);
//         }
//         else {
//             debug();
//             printf("%d\n", query(1, l, r));
//         }
//     }
//
//     return 0;
// }
