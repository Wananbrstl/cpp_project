#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

#define x first
#define y second

using namespace std;

typedef pair<double, double> PDD;

const int N = 510;
const double eps = 1e-8;

struct Line
{
    PDD st, ed; //记录当前直线的起点坐标和终点坐标
}line[N]; //存储所有直线

int n, m;
int cnt; //记录边的数量
int q[N]; //双端队列
PDD pg[N]; //存储凸多边形的所有点的临时数组
PDD res[N]; //存储半平面交上的所有点

int sign(double x) //判断 x 的正负性
{
    if(fabs(x) < eps) return 0;
    if(x < 0) return -1;
    return 1;
}

int dcmp(double x, double y) //比较 x 和 y 的大小
{
    if(fabs(x - y) < eps) return 0;
    if(x < y) return -1;
    return 1;
}

double get_angle(const Line &a) //求向量 a 的角度
{
    return atan2(a.ed.y - a.st.y, a.ed.x - a.st.x);
}

PDD operator-(PDD a, PDD b) //重载减号运算法
{
    return {a.x - b.x, a.y - b.y};
}

double cross(PDD a, PDD b) //计算 a 和 b 的叉积
{
    return a.x * b.y - a.y * b.x;
}

double area(PDD a, PDD b, PDD c) //计算 ab 和 ac 构成的平行四边形的有向面积
{
    return cross(b - a, c - a);
}

bool cmp(const Line &a, const Line &b) //比较函数：按照直线的角度从小到大排序
{
    double A = get_angle(a), B = get_angle(b);
    if(!dcmp(A, B)) return area(a.st, a.ed, b.ed) < 0; //如果两条直线角度相同，则将靠左的排在前面
    return A < B;
}

PDD get_line_intersection(PDD p, PDD v, PDD q, PDD w) //求两个点向式直线的交点
{
    PDD u = p - q;
    double t = cross(w, u) / cross(v, w);
    return {p.x + v.x * t, p.y + v.y * t};
}

PDD get_line_intersection(Line a, Line b) //求直线 a 和直线 b 的交点
{
    return get_line_intersection(a.st, a.ed - a.st, b.st, b.ed - b.st);
}

bool on_right(Line &a, Line &b, Line &c) //判断 b 和 c 的交点是否在 a 的右侧
{
    PDD o = get_line_intersection(b, c); //求 b 和 c 的交点
    return sign(area(a.st, a.ed, o)) <= 0;
}

double half_plane_intersection() //求半平面交
{
    sort(line, line + cnt, cmp); //将所有直线按照角度从小到大排序
    int hh = 0, tt = -1;
    for(int i = 0; i < cnt; i++)
    {
        if(i && !dcmp(get_angle(line[i]), get_angle(line[i - 1]))) continue; //角度相同的直线只考虑最靠左的一条
        while(hh + 1 <= tt && on_right(line[i], line[q[tt - 1]], line[q[tt]])) tt--; //删除队尾无用直线
        while(hh + 1 <= tt && on_right(line[i], line[q[hh]], line[q[hh + 1]])) hh++; //删除队头无用直线
        q[++tt] = i; //将当前直线加入队列
    }
    while(hh + 1 <= tt && on_right(line[q[hh]], line[q[tt - 1]], line[q[tt]])) tt--; //用队头更换队尾
    while(hh + 1 <= tt && on_right(line[q[tt]], line[q[hh]], line[q[hh + 1]])) hh++; //用队尾更新队头

    q[++tt] = q[hh]; //将队头重复加入队尾
    int k = 0;
    //求出半平面交上的所有顶点
    for(int i = hh; i < tt; i++){
        res[k++] = get_line_intersection(line[q[i]], line[q[i + 1]]);
        printf("intersection point : (%lf, %lf)\n", res[k-1].x, res[k-1].y);
    }

    double ans = 0; //记录半平面交的面积
    for(int i = 1; i + 1 < k; i++) ans += area(res[0], res[i], res[i + 1]); //求半平面交（凸多边形）的面积
    return ans / 2;
}

int main()
{
    scanf("%d", &n);
    while(n--)
    {
        scanf("%d", &m);
        for(int i = 0; i < m; i++) scanf("%lf%lf", &pg[i].x, &pg[i].y);
        for(int i = 0; i < m; i++) line[cnt++] = {pg[i], pg[(i + 1) % m]};
    }

    double res = half_plane_intersection(); //求半平面交
    printf("%.3lf\n", res);

    return 0;
}

