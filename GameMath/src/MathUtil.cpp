#include "../include/GameMath//MathUtil.h"
#include "../include/GameMath/Vec3d.h"
#include <cmath>

namespace GameMath {

const Vec3d ZeroVec3d(0.f, 0.f, 0.f);

//\brief 将角度限制在(-pi, pi)中
float 
wrapAngle(float angle)
{
    angle += kPi;
    angle -= std::floor(angle * k1Over2Pi) * k2Pi;
    angle -= kPi;
    return angle;
}

// \breief 安全反三角函数
float 
safeAcos(float x)
{
    if(x <= -1.f) {
        return kPi;
    } 
    if(x >= 1.f) {
        return 0.f;
    }
    return acos(x);
}

}// namespace
