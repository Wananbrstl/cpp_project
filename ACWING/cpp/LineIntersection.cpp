#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

#define EPS 1e-8

using namespace std;

struct Point {
    double x, y;
    Point() :
        x(0), y(0){}
    Point(double _x, double _y) : 
        x(_x), y(_y){}

    Point operator+(const Point& other) const {return Point(x + other.x, y + other.y);}
    Point operator-(const Point& other) const {return Point(x - other.x, y - other.y);}
    Point operator/(double k) const {return Point(x/k, y/k);}
    Point operator*(double k) const  {return Point(x*k, y*k);}

};

struct Line{
    Point pt[2];
    Line(Point p1, Point p2) {
        pt[0] = p1;
        pt[1] = p2;
    }
    Line() {
        pt[0] = Point(0,0);
        pt[1] = Point(0,0);
    }
};

typedef Point Vec;

int sign(double a) {
    if( abs(a) < EPS) return 0;
    return a > 0 ? 1 : -1;
}
double dot(const Vec& a, const Vec& b){
    return a.x * b.x + a.y * b.y;
}
double cross(const Vec& a, const Vec& b) {
    return a.x * b.y - a.y * b.x;
}
double norm(const Vec& a){
    return a.x * a.x + a.y * a.y;
}
double dist(Point a,Point b){
    return sqrt(norm(a-b));
}
Point getCrossPoint_(const Point& p, const Vec& v, const Point& q, const Vec& w) {
    Vec u = p - q;
    double k = cross(w, u) / cross(v, w);
    return p + v * k;
}
Point getCrossPoint(const Point& a, const Point& b, const Point& c, const Vec& d) {
    return getCrossPoint_(a, b-a, c, d-c);
}
bool isIntersect(const Point& a, const Point& b, const Point& c, const Point& d){
    if( max(a.x, b.x) < min(c.x, d.x) || 
        max(a.y, b.y) < min(c.y, d.y) ||
        max(c.x, d.x) < min(a.x, b.x) || 
        max(c.y, d.y) < min(a.y, b.y))
        return false;
    if( sign(cross(b-a, c-a)) * sign(cross(b-a, d-a)) > 0 || 
        sign(cross(d-c, a-c)) * sign(cross(d-c, b-c)) > 0)
        return false;
    return true;
}
vector<Point> getIntersection(const vector<Line>& lines) {
    const int n = lines.size();

}

int main (int argc, char *argv[])
{
       
    return 0;
}
