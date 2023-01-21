#ifndef POINT_H_
#define POINT_H_ 

#include <assert.h>
#include <iostream>

namespace lbn {

/*   Point Class   */
template<class T>
class Point {
private:
    T x_, y_;
    
public:
    Point(T x, T y) :
        x_(x), y_(y) {}

    Point() : 
        x_(T(0)), y_(T(0)) {}

    ~Point() {}

public:
    T& X() {return x_;}
    T& Y() {return y_;}

    inline T X() const {return x_;}
    inline T Y() const {return y_;}

    T& operator[](int idx) {
        assert(idx >= 0 && idx <= 1);
        return idx == 0 ? x_ : y_;
    }

    template<class Pt_Ty>
    friend std::ostream& operator<<(std::ostream& os, const Point<Pt_Ty>& pt);

};

template<class T>
std::ostream& operator<<(std::ostream& os, const Point<T>& pt) {
    os << "[" << pt.x_ << "," << pt.y_ << "]  ";
    return os;
}

} // namespace 

#endif // POINT _H_
