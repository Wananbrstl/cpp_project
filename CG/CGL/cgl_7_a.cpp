/* 打印的重要性!!!! */
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <math.h>

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

double getDistanceSP(const Line& line, const Point& p) {
    if(dot(line.pt[1] - line.pt[0], p - line.pt[0]) < 0.0) return sqrt(norm( p - line.pt[0]));
    if(dot(line.pt[0] - line.pt[1], p - line.pt[1]) < 0.0) return sqrt(norm( p - line.pt[1]));
    return getDIstanceLP(line, p);
}

double getDistance(Line lin1, Line lin2) {
    if(isIntersect(lin1, lin2)) return 0.0;
    // std::cout << lin2.pt[0] << lin2.pt[1] << lin1.pt[1] << std::endl;
    return min({getDistanceSP(lin1, lin2.pt[0]), 
                getDistanceSP(lin1, lin2.pt[1]),
                getDistanceSP(lin1, lin2.pt[1]),
                getDistanceSP(lin1, lin2.pt[1])}),
                4;
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



Circle* cirs;
int main() {
    int N = 2;
    cirs = (Circle*)malloc(sizeof(Circle)*N);
    for(int i = 0; i < N; ++i) {
        scanf("%lf%lf%lf", &cirs[i].origin.x, &cirs[i].origin.y, &cirs[i].r);
    }
    printf("%d\n", ccw(cirs[0], cirs[1]));
    free(cirs);
    return 0;
}
