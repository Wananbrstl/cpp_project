# 基础知识

编程的一些基本原则：

少使用三角函数和除法，这样是为了好的精度。

- $\pi$的求法：

$\pi = acos(-1)$

- 勾股定理

$c^2 = a^2 + b^2 - 2ac \cos(<a,c>)$

a/b/c分别对应三条边

- 正弦定理

$ \frac{\sin(a)}{A} = \frac{\sin(b)}{B} =\frac{\sin(c)}{C} $

- 余弦定理

$ a^2 + b^2 - c^2 = \frac{\cos(<a,b>)}{2ab} $

一些常用操作：

## 点与直线的关系

- 线段是否平行：cross(a, b) == 0? 平行 : 不平行
- 线段是否相交： 跨立判断以及左右值判断(toLeftTest)
```c++
int toLeftTest(Point a, Point b, Point c) {
    return sign(cross(b-a, c-a));
}
```
- 线段之间的交点，首先要**有交点**才能计算：
``` c++
Point getInterPoint(const Line& a, const Line& b) {
    Vec base = b[1] - b[0];
    double b1 = fabs(cross(base, a[0] - b[0]));
    double b2 = fabs(cross(base, a[1] - b[0]));
    double k = b1 / (b1 + b2);
    return a[0] + (a[1] - a[0]) * ;
}
```
- 点到直线的距离，可以通过投影点进行计算
```c++
double getDistPL(const Point& p, const Line& l){
    Point pro = project(p, l); 
    return dist(p, pro);
}
```
- **点到线段的距离**，注意和直线的区别，在于直线的长度无限长，线段的长度有限
```c++
double getDistPS(cosnt Point& p, const Line& seg) {
    Vec base1 = seg[1] - seg[0];
    Vec base2 = seg[0] - seg[1];
    if(dot(base1, p - seg[0]) <= 0) return dist(p, seg[1]);
    if(dot(base2, p - seg[1]) <= 0) return dist(p, seg[0]);
    return getDistPL(p, s);
}
```
- 点关于直线的镜像点，$p' = 2project - p$
```c++
Point mirror(const Point& p, const Line& l) {
    Point ptj = project(p, l);
    return ptj * 2 - p;
}
```
- 一个点是否在直线上，直接通过叉积判断
```c++
bool onSegment(const Point& p, const Line& l) {
    return feq(cross(p - l[0], l[1] - l[0]), 0);
}
```

## 三角形

### 四大心
- 内心：内接圆的圆心
内心到三条边的距离都是$r$，于是有$S = (A+B+C)*r/2$，直接可以得到$r = 2S/(A+B+C)$

坐标公式可以通过求解线性方程：

\begin{align}
    (x-x_1)^2 + (y-y_1)^2 = (x-x_2)^2 + (y-y_2)^2 \\
    (x-x_1)^2 + (y-y_1)^2 = (x-x_3)^2 + (y-y_3)^2 \\
\end{align}
得到内心坐标

- 外心：外接圆的圆心
圆心坐标: $x = \frac{A * x_a + B * x_b + C * x_c}{A + B + C}$
注意这里的$A$与$x_a$是对应的关系

- 垂心：
- 重心

## 多边形

通常按逆时针存储所有点

- 分类
    -多边形
            由在同一平面且不再同一直线上的多条线段首尾顺次连接且不相交所组成的图形叫多边形
    - 简单多边形
            简单多边形是除相邻边外其它边不相交的多边形
    - 凸多边形
      过多边形的任意一边做一条直线，如果其他各个顶点都在这条直线的同侧，则把这个多边形叫做凸多边形
            任意凸多边形外角和均为360°
            任意凸多边形内角和为(n−2)180°
    
- 判断一个点是否在多边形内部
    - 射线法，任意 
