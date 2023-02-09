#include <bits/stdc++.h>
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

struct Point {
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
};

struct Line {
    Line() {
        pt[0] = pt[1] = Point(0.0, 0.0);
    }
    Line(const Point& p1, const Point& p2) {
        pt[0] = p1;
        pt[1] = p2;
    }
    
    Point pt[2];
};

typedef Point Vec;

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

int linePointType(const Line& line, const Point& point) {
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

int main() {
    Line line;
    for(int i=0; i < 2; ++i) 
        cin >> line.pt[i].x >> line.pt[i].y;
    int N; 
    cin >> N;
    for(int i = 0; i < N; ++i) {
        Point query;
        cin >> query.x >> query.y;
        switch (linePointType(line, query)) {
            case ONLINE_BACK:
                printf("ONLINE_BACK\n"); break;
            case ONLINE_FRONT:
                printf("ONLINE_FRONT\n"); break;
            case ON_SEGMENT:
                printf("ON_SEGMENT\n"); break;
            case COUNTER_CLOCKWISE:
                printf("COUNTER_CLOCKWISE\n"); break;
            case CLOCKWISE:
                printf("CLOCKWISE\n"); break;
            default: break;
        }
    }
    return 0;
}
