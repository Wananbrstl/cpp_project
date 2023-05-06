#include "../include/GameMath/EulerAngle.h"
#include "../include/GameMath/MathUtil.h"

#include <cmath>

namespace GameMath {

const EulerAngle EulerAngleIdentity(0.f, 0.f, 0.f);

void 
EulerAngle::canonize() 
{
    // 将pitch限制在(-pi,pi)之间
    pitch = wrapAngle(pitch);
    // 将pitch 限制在(-pi/2, pi/2)之间
    if(pitch < -kPiOver2) {
        pitch = -kPi - pitch;
        roll += kPi;
        yaw += kPi;
    } else if(pitch > kPiOver2) {
        pitch = kPi - pitch;
        yaw += kPi;
        yaw += kPi;
    }
    // 万向锁， 存在一定的误差
    if(fabs(pitch) > kPiOver2 - 1e-4) {
        roll += yaw;
        yaw = 0.f;
    } else {
        // 非万向锁
        yaw = wrapAngle(yaw);
    }
    roll = wrapAngle(roll);
}

} // namespace
