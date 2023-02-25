#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>

#define EPS 1e-12
#define N 100010

const double PI = acos(-1);

using namespace std;

struct Point {
    double x, y;

    Point(double _x, double _y) :
        x(_x), y(_y) {}
    Point() :
        x(0), y(0) {}

    Point operator-(const Point& other) const& {return Point(x - other.x, y - other.y);}
    Point operator+(const Point& other) const& {return Point(x + other.x, y + other.y);}
    Point operator*(double k) const& {return Point(x*k, y*k);}
    Point operator/(double k) const& {return Point(x/k, y/k);}
};

struct Line{
    Point pt[2];
    Line(const Point& p1, const Point& p2) {
        pt[0] = p1;
        pt[1] = p2;
    }
};

struct Circle{
    Point pt;
    double r;
    Circle(const Point& _pt, double _r) :
        pt(_pt), r(_r) {}
};

typedef Point Vec;

int sign(double a){
    if(fabs(a) < EPS) return 0;
    return a > 0 ? 1 : -1;
}
/* a > b => 1*/
int dcmp(double a, double b) {
    return sign(a-b);
}
double cross(Vec vec1, Vec vec2) {
    return vec1.x * vec2.y - vec1.y * vec2.x;
}
double dot(Vec vec1, Vec vec2) {
    return vec1.x * vec2.x + vec1.y * vec2.y;
}
double norm(const Vec& vec){
    return vec.x*vec.x+vec.y*vec.y;
}
double getDistPP(const Point& p1, const Point& p2){
    return sqrt(norm(p2-p1));
}
Point rotate(Point a, double b) {
    return {a.x * cos(b) + a.y * sin(b), -a.x * sin(b) + a.y * cos(b)};
}
Point get_intersection(Point a, Point v, Point b, Point w){ 
    Vec vec = a - b;
    double t = cross(w, vec) / cross(v, w);
    return a + v * t;
}
Point get_intersection(const Line& l1, const Line& l2){
    return get_intersection(l1.pt[0], l1.pt[1]-l1.pt[0], l2.pt[0], l2.pt[1]-l2.pt[0]);
}
Circle constructCircle(const Point& a, const Point& b, const Point& c){
    // Point pts[3] = {a, b, c};
    // return getCircumCircle(pts);
    Vec bc = rotate(c - b, PI/2);
    Vec ac = rotate(c - a, PI/2);
    Point pt = get_intersection((b+c)/2, bc, (a+c)/2, ac);
    double r = getDistPP(pt, a);
    return Circle(pt, r);
}

Point pts[N];
int main (int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%lf%lf", &pts[i].x, &pts[i].y);

    Circle c(pts[0], 0);
    for(int i = 1; i < n; ++i) {
        if( getDistPP(pts[i], c.pt) >= EPS + c.r) {
            c = Circle(pts[i], 0);
            for(int j = 0; j < i; ++j) {
                if( getDistPP(pts[j], c.pt) >= EPS + c.r) {
                    c = Circle((pts[i] + pts[j]) * 0.5, getDistPP(pts[i], pts[j]) * 0.5);
                    for(int k = 0; k < j; ++k) {
                        if( getDistPP(pts[k], c.pt) >= c.r + EPS) 
                            c = constructCircle(pts[i], pts[j], pts[k]);
                    }
                }
            }
        }
    }
    printf("%.10lf\n", c.r);
    printf("%.10lf %.10lf\n", c.pt.x, c.pt.y);
    return 0;
}
