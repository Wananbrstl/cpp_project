#include <algorithm>
#include <bits/stdc++.h>
#include <cassert>
#include <cfloat>
#include <cmath>
#include <complex>
#include <cstdio>
#include <limits.h>
#include <math.h>

#define DEBUG 0

#define EPS 1e-10
#define MAX DBL_MAX

using namespace std;


enum {
    COUNTER_CLOCKWISE  = 1,
    CLOCKWISE          = -1, 
    ONLINE_BACK        = 2,
    ONLINE_FRONT       = -2,
    ON_SEGMENT         = 0
};

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
        // return x < p.x;
    }
    
} Vec;

ostream& operator<<(ostream& os, const Point& p) {
    os << " "<< p.x << "," << p.y << " ";
    return os;
}


double abs(const Vec& vec) {
    return sqrt(vec.x*vec.x+vec.y*vec.y);
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

int ccw2(Point p0,Point p1,Point p2){

	Vec a = p1 - p0;
	Vec b = p2 - p0;

	if(cross(a,b) > EPS)return COUNTER_CLOCKWISE;
	if(cross(a,b) < -EPS)return CLOCKWISE;
	if(dot(a,b) < -EPS)return ONLINE_BACK;
	if(norm(a) < norm(b))return ONLINE_FRONT;

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

class Polygon {
public:
    enum {
        OTHER = 0,
        ON_SEGMENT,
        CONTAIN,
    };

    Polygon(){}
    Polygon(int n) : n_(n) {}

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
                return Polygon::ON_SEGMENT;
            if(a.y > b.y) swap(a, b);
            if(a.y < EPS && EPS < b.y && cross(a, b) > EPS) x = !x;
        }
        return (x ? Polygon::CONTAIN : Polygon::OTHER);
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


    vector<Point> convexHull() {
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
        // NOTE: 注意打印的顺序
        // printf("%d\n", top2);
        // int num = 0;
        // for(int i = 0; i < top2; ++i) if(ans[i].y < ans[num].y) num = i;
        // for(int i = num; i < top2; ++i) {
        //     printf("%d %d\n", (int)ans[i].x, (int)ans[i].y);
        // }
        // for(int i = 0; i < num; ++i) {
        //     printf("%d %d\n", (int)ans[i].x, (int)ans[i].y);
        // }
        return vector<Point>(ans, ans+top2);
    }


private:
    int n_;
    vector<Point> pt_;
};


vector<Point> convexCut(const vector<Point>& convex, const Line& line) {
    const int n = convex.size();
    vector<Point> pts;
    for(int i = 0; i < n; ++i) {
        Point a = convex[i], b = convex[(i+1)%n];
        if(ccw2(line.pt[0], line.pt[1], a) != -1) pts.push_back(a);
        if(ccw2(line.pt[0], line.pt[1], a) * ccw2(line.pt[0], line.pt[1], b) == -1) {
            Point cross_point = getCrossPoint(Line(a,b), line);
#if DEBUG
            printf("line1 : (%lf,%lf)-(%lf,%lf)\nline2 : (%lf,%lf)-(%lf,%lf))\n",
                   line.pt[0].x, line.pt[0].y,
                   line.pt[1].x, line.pt[1].y,
                   Line(a,b).pt[0].x, Line(a,b).pt[0].y,
                   Line(a,b).pt[1].x, Line(a,b).pt[1].y
                   );
            printf("cross point is : (%f,%f)\n", cross_point.x, cross_point.y);
#endif
            pts.push_back(cross_point);
        }
    }
    return pts;
}

double calArea(const vector<Point>& G) {
    double area = 0;
    for(int i = 0; i < (int)G.size(); ++i) {
        const Point& p1 = G[i];
        const Point& p2 = G[(i+1)%G.size()];
        area += cross(p1, p2);
    }
    return area * 0.5;
}

static bool cmpy(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}


void Merge(vector<Point>& pts, int left, int right) {
    if(left >= right) return;
    int mid = (left + right)/2;
    int i = left, j = mid+1;
    printf("=============== merge start ==============\n");
    printf("merge from %d to %d\n", left, right);
    printf("before merge information :\n");
    for(int i = left; i <= right; ++i) 
        printf("%f\t%f\n", pts[i].x, pts[i].y);
    vector<Point> res;
    while(i <= mid && j <= right) {
        if(pts[i].y > pts[j].y) res.push_back(pts[j++]);
        else res.push_back(pts[i++]);
    }
    while(i <= mid) res.push_back(pts[i++]);
    while(j <= right) res.push_back(pts[j++]);
    pts = res;
    printf("after merge information:\n");
    for(auto pt : pts) 
        printf("%f\t%f\n", pt.x, pt.y);
}

/* calculate the closed distance of points set */
double calClosePair(vector<Point>& pts, int left, int right) {
    if(left >= right) return DBL_MAX;
    if(left + 1 == right) return abs(pts[left]-pts[right]);
    
    int mid = (left+right)/2;
    // printf("%d %d %d\n", left, mid, right);
    double dist = min(calClosePair(pts, left, mid), calClosePair(pts, mid, right));

    // merge 
    // inplace_merge(pts.begin()+left, pts.begin()+mid, pts.begin()+right, cmpy);
    sort(pts.begin()+left, pts.begin()+right, cmpy);
    // Merge(pts, left, right);

    vector<Point> V;
	for(int i = left; i <= right; i++){
		if(fabs(pts[i].x-pts[mid].x) >= dist)continue;

		for(int j = 0; j < V.size();j++){
			double dx = pts[i].x - V[V.size()-j-1].x;
			double dy = pts[i].y - V[V.size()-j-1].y;
			if(dy >= dist)break;
			dist = min(dist,sqrt(dx*dx+dy*dy));
		}
		V.push_back(pts[i]);
	}
    return dist;
}


vector<Point> pts;
Point pt;
int main() {
    int N = 0; 
    cin >> N;
    for(int i = 0; i < N; ++i) {
        cin >> pt.x >> pt.y;
        pts.push_back(pt);
    }
    sort(pts.begin(), pts.end());
    // for(auto pt : pts)
    //     std::cout << pt.x << "\t" << pt.y << std::endl;
    double res = calClosePair(pts, 0, pts.size()-1);
    printf("%.10lf\n", res);
    return 0;
}


