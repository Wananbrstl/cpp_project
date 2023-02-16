#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>

#define EPS 1e-8

using namespace std;

static inline bool feq(double a, double b) {
    return fabs(a-b)<EPS;
}
static inline bool gr(double a, double b) {
    return a-b>EPS;
}
static inline bool lr(double a, double b) {
    return a-b<-EPS;
}

struct Point
{
    double x, y;
    Point(double _x, double _y) {x=_x;y=_y;}
    Point operator-(const Point& other) {return Point(x-other.x, y-other.y);}
    bool operator<(const Point& other) {
        return feq(x, other.x)?y<other.y:x<other.x;
    }
};
int n;
int top1 = 0, top2 = 0;
Point* pts;
Point* convex;





double cross(Point p1, Point p2){
    return (p1.x*p2.y-p1.y*p2.x);
}

int toLeftTest(Point a, Point b, Point c) {
    double area = cross(b-a, c-a);
    return feq(area,0.0)?0:area;
}

void convexHull() {
    sort(pts, pts+n); // sort first 
    // printf("sorted:...\n");
    // for(int i = 0; i < n; ++i) {
    //     printf("(%lf, %lf)\n", pts[i].x, pts[i].y);
    // }
    for(int i = 0; i < n; ++i) {
        while(top1 > 1 && toLeftTest(convex[top1-2], convex[top1-1], pts[i])<0) // 说明不是顺时针
            top1--;
        convex[top1++] = pts[i];
    }
    // printf("above:\n");
    // for(int i = 0; i < top1; ++i) {
    //     printf("(%lf, %lf)\n", pts[i].x, pts[i].y);
    // }
    // printf("top1 = %d\n",top1);
    top2 = top1;
    for(int i = n-2; i >= 0; --i) { // 倒数第二个点开始 去考验它
        while(top2 > top1 && toLeftTest(convex[top2-2], convex[top2-1], pts[i])<0)  
            top2--;
        convex[top2++] = pts[i];
    }
    top2--; // 重复了一个
}

double calArea() {
    double area = 0.0;
    for(int i = 0; i < top2; ++i) {
        Point fipt = convex[i];
        Point sept = convex[(i+1)%n];
        area += cross(fipt, sept);
    }
    return area * 0.5;
}

int main (int argc, char *argv[])
{
    scanf("%d", &n);
    pts = (Point*)malloc(n*sizeof(Point));
    convex = (Point*)malloc(2*n*sizeof(Point));

    for(int i = 0; i < n; ++i) {
        scanf("%lf%lf", &pts[i].x, &pts[i].y);
    }
    convexHull();
    printf("%d\n", top2);
    int num = 0;
    for(int i  = 1; i < top2; ++i) {
        if(convex[i].y < convex[num].y) num = i;
    }
    for(int i = num; i < top2; ++i) {
        printf("%d %d\n", (int)convex[i].x, (int)convex[i].y);
    }
    for(int i = 0; i < num; ++i) {
        printf("%d %d\n", (int)convex[i].x, (int)convex[i].y);
    }
    
    free(pts);
    free(convex);
    return 0;
}
