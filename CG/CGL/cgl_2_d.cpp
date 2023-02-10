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

ostream& operator<<(ostream& os, const Point& p) {
    os << " "<< p.x << "," << p.y << " ";
    return os;
}

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

int toLeftTest(const Line& line, const Point& point) {
    const double val = area2(line, point) * 0.5;
    if( fabs(val) < EPS) return 0;
    if( val > 0 ) return 1;
    return -1;
}

bool Xor(int a, int b) {
    if(0 == a && 0 == b) return true;
    return a ^ b;
}

bool isIntersect(const Line& line1, const Line& line2) {
    if(max(line1.pt[0].x, line1.pt[1].x) < min(line2.pt[0].x, line2.pt[1].x) || 
       min(line1.pt[0].x, line1.pt[1].x) > max(line2.pt[0].x, line2.pt[1].x) || 
       max(line1.pt[0].y, line1.pt[1].y) < min(line2.pt[0].y, line2.pt[1].y) || 
       min(line1.pt[0].y, line1.pt[1].y) > max(line2.pt[0].y, line2.pt[1].y))
        return false;
    if( !Xor(toLeftTest(line1, line2.pt[0]), toLeftTest(line1, line2.pt[1])) || 
        !Xor(toLeftTest(line2, line1.pt[0]), toLeftTest(line2, line1.pt[1])))
        return false;
    return true;
}

Point getCrossPoint(const Line& line1, const Line& line2) {
    Vec base = line2.pt[1] - line2.pt[0];
    double k1 = abs(cross(base, line1.pt[0] - line2.pt[0]));
    double k2 = abs(cross(base, line1.pt[1] - line2.pt[0]));
    double k = k1 / (k1 + k2);
    return line1.pt[0] + (line1.pt[1] - line1.pt[0]) * k;
}

double getDIstanceLP(Line l, Point p) {
    return abs(cross(l.pt[1] - l.pt[0], p - l.pt[0])) / sqrt(norm(l.pt[1] - l.pt[0]));
}

double getDistanceSP(const Line& line, const Point& p) {
    if(dot(line.pt[1] - line.pt[0], p - line.pt[0]) < 0.0) return sqrt(norm( p - line.pt[0]));
    if(dot(line.pt[0] - line.pt[1], p - line.pt[1]) < 0.0) return sqrt(norm( p - line.pt[1]));
    return getDIstanceLP(line, p);
}

double getDistance(Line lin1, Line lin2) {
    if(isIntersect(lin1, lin2)) return 0.0;
    // std::cout << lin2.pt[0] << lin2.pt[1] << lin1.pt[1] << std::endl;
    return min({ getDistanceSP(lin1, lin2.pt[0]), 
                 getDistanceSP(lin1, lin2.pt[1]), 
                 getDistanceSP(lin2, lin1.pt[0]),
                 getDistanceSP(lin2, lin1.pt[1])}); 
}

void showCCW(int code) {
    switch (code) {
        case ON_SEGMENT :
            printf("ON_SEGMENT\n");
            break;
        case ONLINE_BACK :
            printf("ONLINE_BACK\n");
            break;
        case ONLINE_FRONT :
            printf("ONLINE_FRONT\n");
            break;
        case COUNTER_CLOCKWISE :
            printf("COUNTER_CLOCKWISE\n");
            break;
        case CLOCKWISE :
            printf("CLOCKWISE\n");
            break;
        default:
            break;
    }
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
        printf("%.10f\n", getDistance(lin1, lin2));
    }
    return 0;
}
