#include <bits/stdc++.h>
#include <cstdio>
#include <string>

#define EPS 1e-6
#define MAX 10000

#define DEBUG 1

using namespace std;


bool feq(double a, double b) {
    return fabs(a - b) < EPS;
}

struct Point {
    double x, y;

    Point() {
        x = y = 0.0;
    }
    Point(double _x, double _y) :
        x(_x), y(_y) {}

    Point operator+(const Point& other) {return Point(x + other.x, y + other.y);}
    Point operator-(const Point& other) {return Point(x - other.x, y - other.y);}
    Point operator*(double k) {return Point(x * k, y * k);}
    Point operator/(double k) {return Point(x / k, y / k);}
    bool  operator<(const Point& other) {return feq(x, other.x) ? y < other.y : x < other.x;}
    double cross(const Point& other) { return (x * other.y) - (y * other.x);}

};
typedef Point Vec;


double norm(Point a) {
    return a.x * a.x + a.y * a.y;
}
double abs(Point a, Point b) {
    return sqrt(norm(a-b));
}
double cross(Vec vec1, Vec vec2) {
    return vec1.x * vec2.y - vec1.y * vec2.x;
}


int toLeftTest(Point a, Point b, Point c) {
    Vec vec1 = b - a;
    Vec vec2 = c - a;
    double res = vec1.cross(vec2);
    return feq(res, 0) ? 0 : (res > 0 ? 1 : -1);
}

double Andrew(Point pts[], int n){ 
    if(n < 3) return 0.0;
    // sort by x axis
    sort(pts, pts + n);
#if DEBUG
    printf("sorting...\n");
    for(int i = 0; i < n; ++i) {
        printf("(%lf, %lf)\n", pts[i].x, pts[i].y);
    }
#endif // DEBUG
    Point res[n * 2];
    int top1 = 0, top2 = 0;
    double len = 0.0;
    for(int i = 0; i < n; ++i) {
        while(top1>1 && toLeftTest(res[top1-2], res[top1-1], pts[i]) <= 0) {
            top1--;
        }
#if DEBUG
        printf("(%lf, %lf) : %d push!\n", pts[i].x, pts[i].y, 
               toLeftTest(res[top1-2], res[top1-1], pts[i]));
#endif
        res[top1++] = pts[i];
    }

#if DEBUG
    printf("top1 = %d\n", top1);
#endif
    top2 = top1;
    for(int i = n - 2; i >= 0; --i) {
        while(top2 > top1 && toLeftTest(res[top2-2], res[top2-1], pts[i]) <= 0)  {
#if DEBUG
            printf("(%lf, %lf) : %d pop!\n", res[top2].x, res[top2].y,
                   toLeftTest(res[top1-2], res[top1-1], pts[i]));
#endif
            top2--;
        }
#if DEBUG
        printf("(%lf, %lf) : %d push!\n", pts[i].x, pts[i].y, 
               toLeftTest(res[top1-2], res[top1-1], pts[i]));

#endif
        res[top2++] = pts[i];
    }
    top2 --;
#if DEBUG
    printf("top2 = %d\n", top2);
#endif
    for(int i = 0; i < top2; ++i) {
#if DEBUG
        printf("(%lf, %lf)\n", res[i].x, res[i].y);
#endif // DEBUG
        int fidx = i, sidx = (i + 1) % top2;
        len += abs(res[fidx], res[sidx]);
    }
    return len;
}

Point pts[MAX];
int main (int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) { 
        scanf("%lf%lf", &pts[i].x, &pts[i].y);
    }
    printf("%.10lf\n", Andrew(pts, n));
    return 0;
}
