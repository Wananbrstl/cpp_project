#include <bits/stdc++.h>
#include <complex>
#include <cstdio>

#define EPS 1e-10

using namespace std;


enum {
    COUNTER_CLOCKWISE = 0,
    CLOCKWISE,
    ONLINE_BACK,
    ONLINE_FRONT,
    ON_SEGMENT 
};

typedef struct Point {
    double x, y;
    Point(){
        x = 0.0;
        y = 0.0;
    }
    Point(double x_, double y_) :
        x(x_), y(y_) {}
    Point operator+(const Point& a) const {return Point(a.x + x, a.y + y);}
    Point operator-(const Point& a) const {return Point(x - a.x, y - a.y);}
    Point operator/(double k) {return Point(x/k, y/k);}
    Point operator*(double k) {return Point(x*k, y*k);}
} Vec;

struct Line {
    Line() {
        pt[0] = pt[1] = Point(0.0, 0.0);
    }
    Line(const Point& p1, const Point& p2) {
        pt[0] = p1;
        pt[1] = p2;
    }

    Vec vec() const {
        return pt[1] - pt[0];
    }
    
    Point pt[2];
};


double dot(const Point& a, const Point& b) {
    return (a.x * b.x + a.y * b.y);
}
double cross(const Point& a, const Point& b) {
    return (a.x * b.y - a.y * b.x);
}
double norm(const Point& p) {
    return (p.x * p.x + p.y * p.y);
}
Point projection(const Line& line, const Point& p) {
    Vec base = line.pt[1] - line.pt[0];
    double r = dot(p - line.pt[0], base) / norm(line.pt[1] - line.pt[0]);
    return line.pt[0] + base * r;
}
Point rejection(const Line& line, const Point& p) {
    Point o = projection(line, p);
    return o * 2.0 - p;
}

double area2(const Line& line, const Point& point) {
    Vec vec1(line.pt[1] - line.pt[0]);
    Vec vec2(point - line.pt[0]);
    return cross(vec1, vec2);
}

int ccw(const Line& line, const Point& point) {
    double a2 = area2(line, point);
    if(a2 < -EPS ) return CLOCKWISE;
    else if(a2 > EPS) return COUNTER_CLOCKWISE;
    else{ // one segment
        Vec a = (line.pt[1] - line.pt[0]);
        Vec b = (point - line.pt[0]);
        if(dot(a,b) < -EPS) return ONLINE_BACK;
        if(norm(a) > norm(b)) return ONLINE_FRONT;
    }
    return ON_SEGMENT;
}

bool isOrthogonal(const Line& line1, const Line& line2) {
    if( abs(norm(line1.vec())) < EPS) return false;
    return fabs(dot(line1.vec(), line2.vec())) < EPS;
}

bool isParallel(const Line& line1, const Line& line2) {
    if( abs(norm(line1.vec())) < EPS) return false;
    return fabs(cross(line1.vec(), line2.vec())) < EPS;
}

Line lin1, lin2;

int main() {
    int N; 
    cin >> N;
    for(int i = 0; i < N; ++i) {
        cin >> lin1.pt[0].x >> lin1.pt[0].y 
            >> lin1.pt[1].x >> lin1.pt[1].y 
            >> lin2.pt[0].x >> lin2.pt[0].y 
            >> lin2.pt[1].x >> lin2.pt[1].y;
        if(isOrthogonal(lin1, lin2)) printf("1\n");
        else if(isParallel(lin1, lin2)) printf("2\n");
        else printf("0\n");
    }
    return 0;
}
