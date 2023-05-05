#include "GameMath/Vec3d.h"

#include <iostream>
#include <cmath>

namespace GameMath{

Vec3d::Vec3d() :
    x(0.f), y(0.f), z(0.f) {}

Vec3d::Vec3d(float _x, float _y, float _z) : 
    x(_x), y(_y), z(_z) {}

Vec3d&
Vec3d::operator=(const Vec3d& a)
{
    x = a.x;
    y = a.y;
    z = a.z;
    return *this;
}

Vec3d 
Vec3d::operator*(float k) const 
{
    return Vec3d(k*x, k*y, k*z);
}

Vec3d&
Vec3d::operator*=(float k) 
{
    x *= k, y *= k, z *= k;
    return *this;
}

Vec3d
Vec3d::operator/(float k)const
{
    return Vec3d(x/k, y/k, z/k);
}
Vec3d& 
Vec3d::operator/=(float k)
{
    x /= k, y /= k, z /= k;
    return *this;
}

bool
Vec3d::operator==(const Vec3d& a) const
{
    return x == a.x && y == a.y && z == a.z;
}

bool 
Vec3d::operator!=(const Vec3d& a) const 
{
    return x != a.x || y != a.y || z != a.z;
}

Vec3d
Vec3d::operator+(const Vec3d& other) const
{
    return Vec3d(x + other.x, y + other.y, z + other.z);
}

Vec3d
Vec3d::operator-(const Vec3d& other) const
{
    return Vec3d(x - other.x, y - other.y, z - other.z);
}

Vec3d& 
Vec3d::operator+=(const Vec3d& other)
{
    x += other.x, y += other.y, z += other.z;
    return *this;
}

Vec3d& 
Vec3d::operator-=(const Vec3d& other)
{
    x -= other.x, y -= other.y, z -= other.z;
    return *this;
}

void 
Vec3d::setZero()
{
    x = y = z = 0;
}

void
Vec3d::normalize()
{
    float k = sqrt(x*x + y*y + z*z);
    operator/=(k);
}

std::ostream&
operator<<(std::ostream& os, Vec3d& v)
{
    os << "(" << v.x << "," << v.y << "," << v.z << ")";
    return os;
}

/* non-member function */
float
dot(const Vec3d& v1, const Vec3d& v2)
{
    return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}

// Vec3d
// cross(const Vec3d& v1, const Vec3d& v2)
// {
//
// }

float
getDistance(const Vec3d& a, const Vec3d& b)
{
    return sqrt(dot(a, b));
}

} //namespace


