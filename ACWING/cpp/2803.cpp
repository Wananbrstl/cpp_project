#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cmath>

#define EPS 1e-8
#define x first
#define y second
#define N 600

using namespace std;

typedef pair<double, double> Point;
typedef Point Vec;

bool feq(double a, double b) {
    return fabs(a-b) < EPS;
}
int dcmp(double a, double b){
    if(feq(a, b)) return 0;
    return a - b > 0 ? 1 : -1;
}
int sign(double a) {
    if(feq(a, 0)) return 0;
    return a > 0 ? 1 : -1;
}
Point operator-(Point a, Point b) {
    return {a.x-b.x, a.y-b.y};
}
Point operator+(Point a, Point b) {
    return {a.x+b.x, a.y+b.y};
}
Point operator*(Point a, double k) {
    return {a.x*k, a.y*k};
}
Point operator/(Point a, double k) {
    return {a.x/k, a.y/k};
}
double dot(Vec a, Vec b) {
    return a.x*b.x+a.y*b.y;
}
double norm(Vec vec) {
    return vec.x*vec.x+vec.y*vec.y;
}
double dist(Point p1, Point p2) {
    return sqrt(norm(p1-p2));
}
double cross(Vec a, Vec b) {
    return a.x * b.y - a.y * b.x;
}
double cross(Point a, Point b, Point c) {
    return cross(b-a, c-a);
}
double area(Point a, Point b, Point c) {
    return cross(b-a, c-a);
}

/* line */
struct Line {
    Point p1, p2;
} Lines[N];

/* get line angle*/
double getAngle(const Line& a) {
    Vec vec = a.p2 - a.p1;
    return atan2(vec.y, vec.x);
}
/* compare with angle */
bool cmp(const Line& l1, const Line& l2){
    double theta1 = getAngle(l1);
    double theta2 = getAngle(l2);
    if(!dcmp(theta1, theta2)) return area(l1.p1, l1.p2, l2.p2) < 0;
    return theta1 < theta2;
}
/* get two line intersection point*/ 
Point getCrossPoint(const Line& line1, const Line& line2) {
    Vec base = line2.p2 - line2.p1;
    double b1 = fabs(cross(base, line1.p1 - line2.p1));
    double b2 = fabs(cross(base, line1.p2 - line2.p1));
    double k = b1 / (b1 + b2);
    return Point(line1.p1 + (line1.p2 - line1.p1) * k);
}
/* to left test 0/-1/1 */
int toLeftTest(Vec vec1, Vec vec2) {
    return sign(cross(vec1, vec2)*0.5);
}
Point get_line_intersection(Point p, Point v, Point q, Point w) //求两个点向式直线的交点
{
    Point u = p - q;
    double t = cross(w, u) / cross(v, w);
    return {p.x + v.x * t, p.y + v.y * t};
}

Point get_line_intersection(Line a, Line b) //求直线 a 和直线 b 的交点
{
    return get_line_intersection(a.p1, a.p2 - a.p1, b.p1, b.p2 - b.p1);
}
/* to left test*/
/* test l1 whether on left of l2-l3 
 * -1 -- on right of l2-l3
 * 0 -- on l2-l3
 * 1 -- on left of l2-l3
*/
int toLeftTest(const Line& l1, const Line& l2, const Line& l3) {
    Point pt = getCrossPoint(l2, l3);
    Vec vec1 = l1.p2 - l1.p1;
    Vec vec2 = pt - l1.p1;
    return toLeftTest(vec1, vec2);
}
bool on_right(Line &a, Line &b, Line &c) //判断 b 和 c 的交点是否在 a 的右侧
{
    Point o = get_line_intersection(b, c); //求 b 和 c 的交点
    return sign(area(a.p1, a.p2, o)) <= 0;
}
Point pts[N], ans[N];
int q[N];
int cnt = 0;
int hh = 0 , tt = -1;

double half_plane_intersection() {
    sort(Lines, Lines+cnt, cmp);
    // for(int i = 0; i < cnt; ++i) {
    //     printf("%lf %lf\n", Lines[i].p1.x, Lines[i].p1.y);
    // }
    for(int i = 0; i < cnt; ++i) {
        if(i && !dcmp(getAngle(Lines[i]), getAngle(Lines[i-1]))) continue;
        while(hh + 1 <= tt && on_right(Lines[i], Lines[q[tt-1]], Lines[q[tt]])) tt--;
        while(hh + 1 <= tt && on_right(Lines[i], Lines[q[hh]], Lines[q[hh+1]])) hh++;
        q[ ++tt] = i;
    }
    while(hh + 1 <= tt && on_right(Lines[hh], Lines[q[tt-1]], Lines[q[tt]])) tt--;
    while(hh + 1 <= tt && on_right(Lines[tt], Lines[q[hh]], Lines[q[hh+1]])) hh++;
    q[ ++tt] = q[hh];
    int k = 0;
    for(int i = hh; i < tt; ++i)  {
        ans[k++] = getCrossPoint(Lines[q[i]], Lines[q[i+1]]);
        // printf("(%lf %lf)-(%lf %lf) --- (%lf %lf) - (%lf %lf)\n",
        //     Lines[q[i]].p1.x, Lines[q[i]].p1.y, 
        //     Lines[q[i]].p2.x, Lines[q[i]].p2.y,
        //     Lines[q[i+1]].p1.x, Lines[q[i+1]].p1.y, 
        //     Lines[q[i+1]].p2.x, Lines[q[i+1]].p2.y );
    }
    double res = 0.0;
    for(int i = 1; i + 1< k; ++i) 
        res += cross(ans[0], ans[i], ans[i+1]);
    return res / 2;
}
int main (int argc, char *argv[])
{
    int n;
    cin >> n;
    while (n--) {
        int m; scanf("%d", &m);
        for(int i = 0; i < m; ++i) 
            scanf("%lf%lf", &pts[i].x, &pts[i].y);
        for(int i = 0; i < m; ++i){
            Lines[cnt++] = {pts[i], pts[(i+1)%m]};
        }
    }
    printf("%.10lf\n", half_plane_intersection());
    // Point a = {0, 0};
    // Point b = {8, 0};
    // Point c = {0, 4};
    // Point d = {2, -4};
    // Line l1, l2;
    // l1.p1 = a;
    // l1.p2 = b;
    // l2.p1 = c;
    // l2.p2 = d;
    // Point p = getCrossPoint(l1, l2);
    // cout << p.x << "\t" << p.y << endl;
    return 0;
}
