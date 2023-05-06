#ifndef VEC3D__H__
#define VEC3D__H__

#include <iostream>

namespace GameMath{

/*
    NOTE: 几个思考的问题
    1. 成员变量使用数组形式还是直接是x,y,z形式
    2. 有必要将变量封装成private吗
    3. 如果成员函数不改变成员变量值，一定要设置成const
    4. 注意operator=, /=, +=,等形式需要返回其引用形式，和内置类型int保持一致
    5. 使用成员函数还是非成员函数去定义函数？需要看场合，effective c++中有提及
    6. float/double的选取？
*/
class Vec3d{
public:
    float x, y, z;

public:
    Vec3d();
    Vec3d(float x, float y, float z);
    Vec3d(const Vec3d& other) = default;

    Vec3d& operator=(const Vec3d& other);
    Vec3d operator*(float k) const;
    Vec3d& operator*=(float k);
    Vec3d operator/(float k) const;
    Vec3d& operator/=(float k);

    bool operator==(const Vec3d& other) const;
    bool operator!=(const Vec3d& other) const;
    Vec3d operator+(const Vec3d& other) const;
    Vec3d operator-(const Vec3d& other) const;
    Vec3d& operator+=(const Vec3d& other);
    Vec3d& operator-=(const Vec3d& other);

    void setZero();
    void normalize();

    friend std::ostream& operator<<(std::ostream& os, Vec3d& v);
};

/* non-member function */
float dot(const Vec3d& v1, const Vec3d& v2);
// Vec3d cross(const Vec3d& v1, const Vec3d& v2);
float getDistance(const Vec3d& a, const Vec3d& b);

extern const Vec3d ZeroVec3d;

} // namespace
#endif //

