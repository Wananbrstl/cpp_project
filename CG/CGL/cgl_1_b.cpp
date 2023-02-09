#include <bits/stdc++.h>

using namespace std;

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

int main() {
    Line line;
    for(int i=0; i < 2; ++i) 
        cin >> line.pt[i].x >> line.pt[i].y;
    int N; 
    cin >> N;
    for(int i = 0; i < N; ++i) {
        Point query;
        cin >> query.x >> query.y;
        Point ans = rejection(line, query);
        printf("%.10lf %.10lf\n", ans.x, ans.y);
    }
    return 0;
}
