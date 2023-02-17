/* 打印的重要性!!!! */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <random>

#define DEBUG 1

#define EPS 1e-10
#define MAX 1e10

using namespace std;

/* arrary rotate from 0-idx*/
template<class T>
void arrRotate(T nums[], int n, int idx) {
    reverse(nums, nums+idx);
    reverse(nums+idx+1, nums+n);
    reverse(nums, nums+n);
}

double min(double arr[], int n) {
    double res = MAX;
    for(int i =  0; i < n; ++i) {
        res = min(res, arr[i]);
    }
    return res;
}

double add(double a, double b) {
    if(fabs(a + b) < EPS*(fabs(a)+fabs(b))) return 0.0;
    return a + b;
}

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
    bool operator<(const Point& p) const {
        return (abs(x - p.x) < EPS) ? (y - p.y) < -EPS : x - p.x < -EPS;
    }
    
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
double abs(const Point& p) {
    return sqrt(norm(p));
}
/*
* 0 -- on line
* 1 -- 第一象限
* 2 -- 第二象限
* 3 -- 第三象限
* 4 -- 第四象限
*/
int witch(const Point& p1, const Point& p2) {
    Point help(1, 0);
    Vec vec1 = help - p1;
    Vec vec2 = p2 - p1;
    int cross_res = cross(vec1, vec2);
    int dot_res = dot(vec1, vec2);
    if(dot_res == 0 || cross_res == 0)  return 0;
    if(dot_res > 0 && cross_res > 0 ) return 1;
    if(dot_res < 0 && cross_res < 0 ) return 2;
    if(dot_res < 0 && cross_res < 0 ) return 3;
    if(dot_res > 0 && cross_res < 0 ) return 4;
    assert(1);
    return 0;
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
    if(a2 < -EPS ) return ::CLOCKWISE;
    else if(a2 > EPS) return ::COUNTER_CLOCKWISE;
    else{ // one segment
        Vec a = (line.pt[1] - line.pt[0]);
        Vec b = (point - line.pt[0]);
        if(dot(a,b) < -EPS) return ::ONLINE_BACK;
        if(norm(a) < norm(b)) return ::ONLINE_FRONT;
    }
    return ::ON_SEGMENT;
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
//
// double getDistanceSP(const Line& line, const Point& p) {
//     if(dot(line.pt[1] - line.pt[0], p - line.pt[0]) < 0.0) return sqrt(norm( p - line.pt[0]));
//     if(dot(line.pt[0] - line.pt[1], p - line.pt[1]) < 0.0) return sqrt(norm( p - line.pt[1]));
//     return getDIstanceLP(line, p);
// }
//
// double getDistance(Line lin1, Line lin2) {
//     if(isIntersect(lin1, lin2)) return 0.0;
//     // std::cout << lin2.pt[0] << lin2.pt[1] << lin1.pt[1] << std::endl;
//     return min({getDistanceSP(lin1, lin2.pt[0]), 
//                 getDistanceSP(lin1, lin2.pt[1]),
//                 getDistanceSP(lin1, lin2.pt[1]),
//                 getDistanceSP(lin1, lin2.pt[1])}),
//                 4;
// }
//
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

class Ploygon {
public:
    enum {
        OTHER = 0,
        ON_SEGMENT,
        CONTAIN,
    };

    Ploygon(){}
    Ploygon(int n) : n_(n) {}

    void add(const Point& pt) {
        pt_.push_back(pt);
    }
    Point get(int i)  const {
        assert(i >= 0 && i < pt_.size());
        return pt_[i];
    }

    double calArea() const {
        double area = 0.0;
        for(int i = 0; i < pt_.size() ; ++i) {
            int first_idx = i;
            int second_idx = (i + 1) % pt_.size();
            area += cross(pt_[first_idx], pt_[second_idx]);
        }
        return area * 0.5;
    }

    bool isConvex() const {
        for(int i = 1; i < pt_.size(); ++i) {
            int fidx = i-1, sidx = i, trdidx = (i+1)%pt_.size();
            if(toLeftTest(Line(pt_[fidx], pt_[sidx]), pt_[trdidx]) < 0) 
                return false;
        }
        return true;
    }

    /* contain, on segment, other*/
    /* BUG: 为什么？ */
    int COO(const Point& tar) const {
        bool x = false;
        for(int i = 0; i < pt_.size(); ++i) {
            Vec a = pt_[i] - tar;
            Vec b = pt_[(1+i)%pt_.size()] - tar;
            if( abs(cross(a, b)) < EPS && (dot(a, b)) < EPS) 
                return Ploygon::ON_SEGMENT;
            if(a.y > b.y) swap(a, b);
            if(a.y < EPS && EPS < b.y && cross(a, b) > EPS) x = !x;
        }
        return (x ? Ploygon::CONTAIN : Ploygon::OTHER);
    }

    /* return LLT point idx*/
    int LLT() const {
        int idx = 0;
        for(int i = 1; i <pt_.size(); ++i) {
            if(pt_[i].y < pt_[idx].y ||  // last
               (pt_[i].y == pt_[idx].y && pt_[i].x < pt_[idx].x)) { // then left
                idx = i;
            }
        }
        return idx;
    }


    void convexHull() {
        sort(pt_.begin(), pt_.end());
#if DEBUG
        printf("sorting result: \n");
        for(auto pt: pt_) cout << pt.x << "\t" << pt.y << endl;
#endif
        int top1 = 0;
        int top2 = 0;
        Point ans[pt_.size() * 2];
#if DEBUG
        printf("above half start!\n");
#endif
        for(int i = 0; i < (int)pt_.size(); ++i) { 
            while (top1 > 1 && cross(ans[top1-2]-ans[top1-1], pt_[i]-ans[top1-1] ) > 0) {
#if DEBUG
            printf("%d-th point (%f, %f) pop!\n", top1-1, ans[top1-1].x, ans[top1-1].y);
#endif
                top1--;
            }
#if DEBUG
        printf("%d-th point (%f, %f) push!\n", i, pt_[i].x, pt_[i].y);
#endif
            ans[top1++] = pt_[i];
        }
        top2 = top1;
#if DEBUG
        printf("ahead half start!\n");
#endif
        for(int i = (int)pt_.size()-2; i >= 0; --i) {
            while (top2>top1 && cross(ans[top2-2]-ans[top2-1], pt_[i]-ans[top2-1]) > 0) {
#if DEBUG
                printf("%d-th point (%f, %f) pop!\n", i, ans[top2-1].x, ans[top2-1].y);
#endif
                top2--;
            }
            ans[top2++] = pt_[i];
#if DEBUG
            printf("%d-th point (%f, %f) push!\n", i, pt_[i].x, pt_[i].y);
#endif
        }
        // NOTE: 最后包含了开头的一个
        top2--;
        // NOTE: modift the order
        printf("%d\n", top2);
        int num = 0;
        for(int i = 0; i < top2; ++i) if(ans[i].y < ans[num].y) num = i;
        for(int i = num; i < top2; ++i) {
            printf("%d %d\n", (int)ans[i].x, (int)ans[i].y);
        }
        for(int i = 0; i < num; ++i) {
            printf("%d %d\n", (int)ans[i].x, (int)ans[i].y);
        }
    }


private:
    int n_;
    vector<Point> pt_;
};

struct Circle{
    
public:
    Circle() :
         r(0), origin(0,0){};
    Circle(const Point& p, double radius) :
        r(radius), origin(p){};


    double r;
    Point origin;
};

/*
 *   4 -- if not intersection
 *   3 -- if ciruclued
 *   2 -- if intersection
 *   1 -- if inter cicle
 *   0 -- if a circle is inside in another
 */
enum {
    TAGENT_0 = 0,
    TAGENT_1,
    TAGENT_2,
    TAGENT_3,
    TAGENT_4,

};

int ccw(const Circle& cir1, const Circle& cir2) {
    double dist = sqrt(norm(cir1.origin - cir2.origin));
#if DEBUG
    printf("dist = %lf\n", dist);
#endif
    if((dist-cir1.r-cir2.r) > EPS) return TAGENT_4;//不相交
    if(fabs(dist-cir1.r-cir2.r) < EPS)  return TAGENT_3; // 外切

    double minR = min(cir1.r, cir2.r);
    double maxR = max(cir1.r, cir2.r);
    if(fabs(maxR - minR - dist) < EPS) return TAGENT_1;
    if(maxR - minR - dist > EPS) return TAGENT_0; // 包含关系 
    return TAGENT_2;
}

double calArea(Point* pts, int n){
    double res = 0.0;
    for(int i = 0; i < n; ++i) {
        res += cross(pts[i], pts[(i+1)%n]);
    }
    return res*0.5;
}

Circle thrPoint2Circle(Point* pts) {
    const Point& p1 = pts[0];
    const Point& p2 = pts[1];
    const Point& p3 = pts[2];
    Point midPoint12 = p1 + (p2 - p1) * 0.5;
    Point midPoint13 = p1 + (p3 - p1) * 0.5;
    printf("line12 mid point : (%lf, %lf)\n", midPoint12.x, midPoint12.y);
    printf("line13 mid point : (%lf, %lf)\n", midPoint13.x, midPoint13.y);
    Line l1(p3, midPoint12), l2(p2, midPoint13);
    Point origin = getCrossPoint(l1, l2);
    printf("origin point : (%lf, %lf)\n", origin.x, origin.y);
    double r = abs(p1-origin);
    return Circle(origin, r);
}

Circle getCircle(Point* pts) {
    const double dist1 = abs(pts[0] - pts[1]);
    const double dist2 = abs(pts[1] - pts[2]);
    const double dist3 = abs(pts[2] - pts[0]);
    double s = (dist1 + dist2 + dist3) / 2.0;
    s = sqrt(s * (s - dist1) * (s - dist2) * (s - dist3));
    double r = 2 * s / (dist1 + dist2 + dist3) ;
    double x = (pts[0].x * dist2 + pts[1].x * dist3 + pts[2].x * dist1) / (dist1 + dist2 + dist3);
    double y = (pts[0].y * dist2 + pts[1].y * dist3 + pts[2].y * dist1) / (dist1 + dist2 + dist3);
    printf("%.10lf %.10lf %.10lf\n", x, y, r);
    return Circle(Point(x,y), r);
}

Circle getCircumCircle(Point pts[3]){
    const double dist1 = abs(pts[0] - pts[1]);
    const double dist2 = abs(pts[1] - pts[2]);
    const double dist3 = abs(pts[2] - pts[0]);
    double s = (dist1 + dist2 + dist3) / 2.0;
    s = sqrt(s * (s - dist1) * (s - dist2) * (s - dist3));
#if DEBUG
    printf("area is : %lf\n", s);
#endif
    // BUG: 为什么这样的精度不够？？？？？
    double r = dist1*dist2*dist3/(4.0*s);
    double mu = (pts[1].x-pts[0].x)*(pts[2].y-pts[0].y) - (pts[1].y-pts[0].y)*(pts[2].x-pts[0].x);
    double R1 = (pts[1].x*pts[1].x - pts[0].x*pts[0].x + pts[1].y*pts[1].y - pts[0].y*pts[0].y) / 2.0;
    double R2 = (pts[2].x*pts[2].x - pts[0].x*pts[0].x + pts[2].y*pts[2].y - pts[0].y*pts[0].y) / 2.0;
    double f1 = (R1*(pts[2].y-pts[0].y) - R2*(pts[1].y-pts[0].y));
    double f2 = (R2*(pts[1].x-pts[0].x) - R1*(pts[2].x-pts[0].x));
    double x = f1 / mu;
    double y = f2 / mu;
#if DEBUG
    printf("origin to p1's distance is : %lf\n", abs(Point(x,y)-pts[0]));
    printf("origin to p2's distance is : %lf\n", abs(Point(x,y)-pts[1]));
    printf("origin to p3's distance is : %lf\n", abs(Point(x,y)-pts[2]));
#endif
    double rr = abs(Point(x, y)- pts[0]);
    printf("%.12lf %.12lf %.12lf\n", x, y, rr);
    return Circle(Point(x, y), rr);
}

int getCrossPointCL(const Circle& circle, const Line& line, Point& out_pt1, Point& out_pt2){
    const double dist = getDIstanceLP(line, circle.origin);
    out_pt1 = out_pt2 = Point();
    Point prj = projection(line, circle.origin);
    if( abs(dist - circle.r) < EPS) {
        out_pt1 = prj;
        return 1;
    } else if (dist < circle.r) {
        Vec base = (line.pt[1] - line.pt[0]) / abs(line.pt[1] - line.pt[0]);
        double k = sqrt(circle.r * circle.r - norm(prj - circle.origin));
        out_pt1 = prj - base* k;
        out_pt2 = base * k + prj;
        return 2;
    }
    return 0;
}

inline Point polar(double d, double theta) {
    return Point(d*cos(theta), d*sin(theta));
}

inline double arg(const Point& pt) {
    return atan2(pt.y, pt.x);
}
/*  get the cross point of two circles */
void getCrossPointCC(const Circle& circle1, const Circle& circle2, Point& p1, Point& p2) {
    double d = abs(circle1.origin-circle2.origin);
    double ang = acos((circle1.r*circle1.r + d*d - circle2.r*circle2.r)/(2.0*circle1.r*d));
    double t = arg(circle2.origin - circle1.origin);
    if(isnan(d)) printf("d is not a number\n");
    if(isnan(ang)) printf("ang is not a number\n");
    if(isnan(t)) printf("t is not a number\n");
    p1 = circle1.origin+polar(circle1.r, t + ang);
    p2 = circle1.origin+polar(circle1.r, t - ang);
}

Circle c1, c2;
Point p1, p2;
int main(){
    scanf("%lf %lf %lf", &c1.origin.x, &c1.origin.y, &c1.r);
    scanf("%lf %lf %lf", &c2.origin.x, &c2.origin.y, &c2.r);
    getCrossPointCC(c1, c2, p1, p2);
    if(p2 < p1) swap(p1, p2);
    printf("%.10lf %.10lf %.10lf %.10lf\n", p1.x, p1.y, p2.x, p2.y);
    return 0;
}
