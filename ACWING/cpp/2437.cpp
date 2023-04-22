//TODO: 递归和非递归
#include <iostream>
#include <cstring>

using namespace std;

const int N = 100010;

struct Node{
    int son[2], size, v, p;
    bool flag;

    void init(int _p, int _v){
        v = _v; p = _p;
    }

}Tr[N];

int root, idx;


void pushup(int u){
    Tr[u].size = Tr[Tr[u].son[0]].size + Tr[Tr[u].son[1]].size + 1;
}
void pushdown(int u){
    if(Tr[u].flag) {
        swap(Tr[u].son[0], Tr[u].son[1]);
        Tr[Tr[u].son[0]].flag ^= 1;
        Tr[Tr[u].son[1]].flag ^= 1;
        Tr[u].flag = 0;
    }
}

void rotate(int x){
    int y = Tr[x].p, z = Tr[y].p;
    int t = Tr[y].son[1] == x; // 0 -- left 1 -- right son
    Tr[z].son[y == Tr[z].son[1]] = x, Tr[x].p = z;
    Tr[y].son[t] = Tr[x].son[t ^ 1], Tr[Tr[x].son[t^1]].p = x;
    Tr[x].son[t ^ 1] = y, Tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int x, int k){
    while(Tr[x].p != k){
        int y = Tr[x].p, z = Tr[y].p;
        if(z != k) {
            if(Tr[z].son[y == Tr[z].son[1]] ^ Tr[y].son[Tr[y].son[1] == x]) 
                rotate(y);
            else rotate(x);
        }
        rotate(x);
    }   
    if(!k) root = x;
}


void insert(int x){
    int u = root, p = 0;
    while(u)  p = u, u = Tr[u].son[Tr[u].v >= x];
    u = ++idx;
    if(p) Tr[p].son[Tr[p].v < x] = u;
    Tr[u].init(p, x);
    splay(u, 0);
}

int get_k(int root, int k) {
    if(!root) return -1;
    if(Tr[Tr[root].son[0]].size >= k) return get_k(Tr[root].son[0], k);
    else if(Tr[Tr[root].son[0]].size + 1 == k) return Tr[root].v;
    return get_k(Tr[root].son[1], k - Tr[Tr[root].son[0]].size - 1);
}
void output(int root){
    if(!root)return;
    output(Tr[root].son[0]);
    cout << Tr[root].v << " ";
    output(Tr[root].son[1]);
}

int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n + 1; i ++ ) insert(i);
    while (m -- )
    {
        int l, r;
        scanf("%d%d", &l, &r);
        l = get_k(root, l), r = get_k(root, r + 2);
        splay(l, 0), splay(r, l);
        Tr[Tr[r].son[0]].flag ^= 1;
    }
    output(root);
    return 0;
}

