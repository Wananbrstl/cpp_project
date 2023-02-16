#include <iostream>
#include <cstdlib>
#include <limits.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <cstdio>
#define X 0
#define Y 1

#define DEBUG 0
#define NUM 100001
#define MAX 10000000000.0
#define EPS 1e-8

using namespace std;

struct Point{
    double x, y;
    bool operator<(const Point& other) {
        return y < other.y;
    }
    bool operator>(const Point& other) {
        return y > other.y;
    }
};
Point *pts;

static bool cmpy(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}

static bool cmpx(const Point& p1, const Point& p2) {
    return fabs(p1.x-p2.x)<EPS?p1.y<p1.y:p1.x<p2.x;
}


template<class T>
void merge(T* pts, int left, int mid, int right) {
    int i = left, j = mid, cur = left;
    T* res = (T*)malloc(sizeof(T)*(right-left));
    while(i < mid && j < right){
        if(pts[i] > pts[j]) res[cur++] = pts[j++];
        else res[cur++] = pts[i++];
    }
    while(i < mid) res[cur++] = pts[i++];
    while(j < right) res[cur++] = pts[j++];
    for(int x = left; x < right; ++x)
        pts[x] = res[x];
    free(res);
}

double closePair(Point* pts, int n) {
    if(n <= 1) return MAX;

    int mid = n/2;
    double x = pts[mid].x;
    double dist = min(closePair(pts, mid), closePair(pts+mid, n-mid));
#if DEBUG
    printf("================= merge start =================\n");
    printf("before merge :\n");
    for(int i = 0; i < n; ++i) {
        std::cout << pts[i].x << "\t" << pts[i].y << std::endl;
    }
#endif
    merge(pts, 0, mid, n);
    // inplace_merge(pts, pts+mid, pts+n, cmpy);
#if DEBUG
    printf("after merge :\n");
    for(int i = 0; i < n; ++i) {
        std::cout << pts[i].x << "\t" << pts[i].y << std::endl;
    }
#endif

    vector<Point> V;
	for(int i = 0; i < n; i++){
		if(fabs(pts[i].x-x) >= dist)continue;

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
double closest_pair(Point* pts,int n){
    if(n <= 1)return MAX;

    int mid = n/2;
    double x = pts[mid].x;
    double dist = min(closest_pair(pts,mid),closest_pair(pts+mid,n-mid));
    inplace_merge(pts,pts+mid,pts+n,cmpy);

    vector<Point> V;
    for(int i = 0; i < n; i++){
        if(fabs(pts[i].x-x) >= dist)continue;
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

int main() {
    int N;
    scanf("%d", &N);
    pts = (Point*)malloc(sizeof(Point)*N);
    for(int i = 0; i < N; ++i) {
        scanf("%lf%lf", &pts[i].x, &pts[i].y);
    }
    sort(pts, pts+N, cmpx);
#if DEBUG
    printf("sorted:\n");
    for(int i = 0; i < N; ++i) {
        std::cout << pts[i].x << "\t" << pts[i].y << std::endl;
    }
#endif
    printf("%.10lf\n", closePair(pts, N));
    free(pts);
    return 0;
}
