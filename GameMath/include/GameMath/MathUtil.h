#ifndef MATH_UTIL_H_
#define MATH_UTIL_H_

#include <cmath>

namespace GameMath{

/* 预定义常用的计算常数， 目的是加速计算 */
const float kPi = 3.14159265f;
const float k2Pi = kPi * 2.f;
const float kPiOver2 = kPi / 2.f;
const float k1OverPi = 1.f / kPi;
const float k1Over2Pi = 1.f / k2Pi;

/* 角度限制函数 */
extern float wrapAngle(float angle);
/* 安全反三角函数*/
extern float safeAcos(float x);
/* 计算某些平台的sin和cos值 */
inline void sinCos(float* returnSin, float* returnCos, float angle) {
    *returnSin = sin(angle);
    *returnCos = cos(angle);
}

}

#endif
