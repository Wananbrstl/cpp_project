//BUG: 有问题
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define lchild(u) u << 1
#define rchild(u) u << 1 | 1

typedef long long LL;

const int N = 500010;

struct Node {
    int left, right;
    LL sum, d;
} tr[4 * N];

int n, m;
LL nums[N];

LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

void pushUp(Node& u, Node& l, Node& r){
    u.sum = l.sum + r.sum;
    u.d = gcd(l.d, r.d);
}

void pushUp(int u) {
    pushUp(tr[u], tr[lchild(u)], tr[rchild(u)]);
}

void build(int u, int l, int r){
    if(l == r) {
        LL d = nums[l] - nums[l - 1];
        tr[u] = {l, l, d, d};
    } else {
        tr[u].left = l, tr[u].right = r;
        int mid = (l + r) >> 1;
        build(lchild(u), l, mid);
        build(rchild(u), mid+1, r);
        pushUp(u);
    }
}

Node query(int u, int l, int r) {
    if(tr[u].left >= l && r >= tr[u].right) return tr[u];
    int mid = tr[u].left + tr[u].right >> 1;
    if(r <= mid) return query(lchild(u), l, r);
    else if (l > mid) return query(rchild(u), l, r);
    else {
        auto left = query(lchild(u), l, r);
        auto right = query(rchild(u), l, r);
        Node res = {0,0,0,0};
        pushUp(res, left, right);
        return res;
    }
}

void modify(int u, int x, LL v) {
    if(tr[u].left == tr[u].right && tr[u].left == x) {
        LL d = tr[u].sum + v;
        tr[u] = {x, x, d, d};
    } else {
        int mid = tr[u].left + tr[u].right >> 1;
        if(x > mid) modify(rchild(u), x, v);
        else modify(lchild(u), x, v); 
        pushUp(u);
    }
}

int main (int argc, char *argv[])
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) scanf("%lld", &nums[i]);
    build(1, 1, n);
    char op[2];
    int l, r, v;
    while (m--) {
        scanf("%s%d%d", op, &l, &r);
        if(*op == 'Q') {
            Node left = query(1, 1, l);
            Node res = {0,0,0,0};
            if(l + 1 <= r) res = query(1, l+1, r);
            LL ans = abs(gcd(res.d, left.sum));
            printf("%lld\n", ans);
        } else {
            scanf("%d", &v);
            modify(1, l, v);
            if(r + 1 <= n) modify(1, r + 1, -v);
        }
    }
    return 0;
}
