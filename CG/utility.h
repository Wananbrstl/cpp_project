#ifndef UTILITY_H_
#define UTILITY_H_

#include "common.h"

namespace lbn {

/* calculate the area */
template<class T> 
double area2(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) {
    return (p2.X() - p1.X()) * (p3.Y() - p1.Y()) -
           (p3.X() - p1.X()) * (p2.Y() - p1.Y());
}

/* to left test  */
template<class T>
bool toLeftTest(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) {
    return area2(p1, p2, p3) > 0;
}

} // namespace

#endif // UTILITY_H_
