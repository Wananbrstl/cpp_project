#ifndef EULERANGLE_H_
#define EULERANGLE_H_

namespace GameMath {

class Quaternion;
class Matrix4x3;
class RotationMatrix;

/* 
    欧拉角度变换
*/
class EulerAngle{
public:
    float roll;
    float pitch;
    float yaw;

public:
    EulerAngle();
    EulerAngle(float r, float p, float y);

    void identity();
    void canonize();

    /* 从四元数变换到欧拉角 */
    void fromObjectToInertialQuaternion(const Quaternion &q);
    void fromInertialToObjectQuaternion(const Quaternion &q);

    /* 从矩阵到欧拉角 */
    void fromObjectToWorldMatrix(const Matrix4x3 &m);
    void fromWorldToObjectMatrix(const Matrix4x3 &m);

    void fromRotationMatrix(const RotationMatrix& m);
};

extern const EulerAngle EulerAngleIdentity;

} // namespace 

#endif // !EULERANGLE_H_
