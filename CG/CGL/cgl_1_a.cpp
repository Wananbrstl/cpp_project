#include <bits/stdc++.h>
#include <math.h>

struct Point{
public:
    double x, y;

    Point() : x(0), y(0) {}
    Point(double _x, double _y) {
        x = _x;
        y = _y;
    }
    Point(const Point& p) {
        x = p.x;
        y = p.y;
    }

    Point operator+(const Point& other) const {
        return Point(x + other.x, other.y + y);
    }
    Point operator-(Point other) const {
        return Point(x - other.x, y - other.y);
    }
    Point operator*(double k) {
        return Point(x * k, y * k);
    }
    Point operator/(double k){
        return Point(x / k, y / k);
    }

};

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "[" << point.x  <<","<< point.y << "]";
    return os;
}

typedef Point Vec;

double dot(const Point& p, const Point& q){
    return (p.x * q.x + p.y * q.y);
}

Point cross(const Point& p, const Point& q){
    return Point();
}

double norm(const Point& p) {
    return (p.x * p.x + p.y * p.y);
}   

Point project(const Point& p, const Point& q, const Point& query){
    Point base = q - p;
    double r = dot(query - p, base) / norm(q - p); 
    return p + base * r;
}

int main (int argc, char *argv[])
{
    Point p, q;
    int N; 
    std::cin >> p.x >> p.y >> q.x >> q.y;
    std::cin >> N;
    for(int i = 0; i < N; ++i) {
        Point query;
        std::cin >> query.x >> query.y;
        Point ans = project(p, q, query);
        printf("%5f %5f\n", ans.x, ans.y);
    }
    return 0;
}
