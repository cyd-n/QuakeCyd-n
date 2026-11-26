#include "MathLibary.h"

Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

float Vector3::Dot(const Vector3& _other) const {return (float)((float)(x*_other.x) + (float)(y*_other.y) + (float)(z*_other.z)); }

double Vector3::DoublePrecisionDot(const Vector3& _other) const {return (x*_other.x) + (y*_other.y) + (z*_other.z); }

int Vector3::IntPrecisionDot(const Vector3& _other) const {return std::round(Dot(_other)); }

bool Vector3::Compare(const Vector3& _other) const { return x == _other.x && y == _other.y && z == _other.z; }

Vector3 Vector3::Add(const Vector3& _other) const { return Vector3(x + _other.x, y + _other.y, z + _other.z); }
Vector3 Vector3::Add(const float& _other) const { return Vector3(x + _other, y + _other, z + _other); }

Vector3 Vector3::Subtract(const Vector3& _other) const { return Vector3(x - _other.x, y - _other.y, z - _other.z); }
Vector3 Vector3::Subtract(const float& _other) const { return Vector3(x - _other, y - _other, z - _other); }

Vector3 Vector3::Multiply(const Vector3& _other) const { return Vector3(x * _other.x, y * _other.y, z * _other.z); }
Vector3 Vector3::Multiply(const float& _other) const { return Vector3(x * _other, y * _other, z * _other); }

Vector3 Vector3::Divide(const Vector3& _other) const {
    return Vector3((x != 0) ? (_other.x != 0) ? x / _other.x : 0 : 0,
     (y != 0) ? (_other.y != 0) ? y / _other.y : 0 : 0,
     (z != 0) ? (_other.z != 0) ? z / _other.z : 0 : 0);
}
Vector3 Vector3::Divide(const float& _other) const {
    return Vector3((x != 0) ? (_other != 0) ? x / _other : 0 : 0,
     (y != 0) ? (_other != 0) ? y / _other : 0 : 0,
     (z != 0) ? (_other != 0) ? z / _other : 0 : 0);
}

Vector3 Vector3::VectorMultiplyAdd (const Vector3& _scale, const Vector3& _other) const {
    Vector3 result;
    result.x = this->x + _scale.x * _other.x;
    result.y = this->y + _scale.y * _other.y;
    result.z = this->z + _scale.z * _other.z;

    return result;
}
Vector3 Vector3::VectorMultiplyAdd (const double& _scale, const Vector3& _other) const {
    Vector3 result;
    result.x = this->x + _scale * _other.x;
    result.y = this->y + _scale * _other.y;
    result.z = this->z + _scale * _other.z;

    return result;
}

void Vector3::Scale (const Vector3& _scale) {
    x *= _scale.x;
    y *= _scale.y;
    z *= _scale.z;
}
void Vector3::Scale (const double& _scale) {
    x *= _scale;
    y *= _scale;
    z *= _scale;
}

Vector3 Vector3::Cross (const Vector3 _other) {
    Vector3 result;
    result.x = y * _other.z - z * _other.y;
    result.y = z * _other.x - x * _other.z;
    result.z = x * _other.y - y * _other.x;
    return result;
}

void Vector3::Turn(const Vector3& _axis, uint8_t _angle) {
    constexpr float BIN2RAD = (2.0f * PI) / 256.0f;
    float radians = _angle * BIN2RAD;

    float cosTheta = std::cos(radians);
    float sinTheta = std::sin(radians);
    float oneMinusCos = 1.0f - cosTheta;

    Vector3 term1 = this->Multiply(cosTheta);
    Vector3 term2 = _axis.Cross(*this).Multiply(sinTheta);
    float f = _axis.Dot(*this) * oneMinusCos;
    Vector3 term3 = _axis.Multiply(f);

    *this = term1.Add(term2.Add(term3));
}
//TODO: take right and up vectors to properly set yaw and roll, A commit in og source code --Cyd-n
void Vector3::Angles() {
    Vector3 tempV3;

    Vector3 tempV3 = Vector3(x, y, 0);
    x= -atan2(forward.z, tempV3.Magnitude()) / PI_DIV_BY180; // X is now equals to Pitch
    y= atan2(forward.y, forward.x) / PI_DIV_BY180; // Y is now equals to Yaw
    z= 0; // Z is now equals to Roll
}
std::array<Vector3, 3> Vector3::ReturnAngles() const{
    std::array<Vector3, 3> arrayAngles;

    double angle;
    double sineRaw, sinePitch, sineYaw, cosineRaw, cosinePitch, cosineYaw;

    angle = x * (PI * 2 / 360); // X is now equals to Pitch
    sinePitch = std::sin(angle);
    cosinePitch = std::cos(angle);

    angle = y * (PI * 2 / 360); // Y is now equals to Yaw
    sineYaw = std::sin(angle);
    cosineYaw = std::cos(angle);

    angle = z * (PI * 2 / 360); // Z is now equals to Roll
    sineRaw = std::sin(angle);
    cosineRaw = std::cos(angle);

    double cosinePitchYaw = cosinePitch * cosineYaw,
            cosinePitchSineYaw = cosinePitch * sineYaw,
            negativeSinePitch = -sinePitch;

    double negaOneSineRawPitchCosineYawNegaOneRawSineYaw = -1 * sineRaw * sinePitch * cosineYaw + -1 * cosineRaw * -sineYaw,
            negaOneSineRawPitchYawNegaOneCosineRawYaw = -1 * sineRaw * sinePitch * sineYaw + -1 * cosineRaw * cosineYaw,
            negativeSineRawCosinePitch = -1 * sineRaw * cosinePitch;

    double cosineRawSinePitchCosineYawNegaSineRawNegaSineYaw = cosineRaw * sinePitch * cosineYaw + -sineRaw * -sineYaw,
            cosineRawSinePitchYawNegaSineRawCosineYaw = cosineRaw * sinePitch * sineYaw + -sineRaw * cosineYaw,
            cosineRawPitch = cosineRaw * cosinePitch;

    arrayAngles[0] = Vector3(cosinePitchYaw, cosinePitchSineYaw, negativeSinePitch); // forward
    arrayAngles[1] = Vector3(negaOneSineRawPitchCosineYawNegaOneRawSineYaw, negaOneSineRawPitchYawNegaOneCosineRawYaw, negativeSineRawCosinePitch); // right
    arrayAngles[2] = Vector3(cosineRawSinePitchCosineYawNegaSineRawNegaSineYaw, cosineRawSinePitchYawNegaSineRawCosineYaw, cosineRawPitch); // up

    return arrayAngles;
}

Vector3 ProjectPointOnPlane(const Vector3& _normal) const {
    Vector3 result;

    float inverseDenominator = 1.0f / _normal.Dot(_normal);

    float distance = _normal.Dot(*this) * inverseDenominator;

    result = Vector3(x - distance * _normal.x, y - distance * _normal.y, z - distance * _normal.z);

    return result;
}

void Vector3::Inverse() {
    *this = Vector3(-x, -y, -z);
}

float Vector3::Magnitude() const {
    Vector3 thisVector = Vector3(x, y, z);
    return std::sqrt(Dot(*this));
}

void Vector3::Normalize() {
    float mag = Magnitude();

    if (mag > 0.0) {
        float invMag = 1.0f / mag;
        *this = Vector3(x * invMag, y * invMag, z * invMag);
    }
}

Void Vector3::SetPos(int _pos, float _val) {
    switch (_pos) {
        case 0: x = _val; break;
        case 1: y = _val; break;
        case 2: z = _val; break;
    }
}

std::array<Vector3, 3> Vector3::ToArray() {
    std::array<Vector3, 3> result;
    result[0] = x;
    result[1] = y;
    result[2] = z;

    return result;
}

// src is normalized before you set it in the PerpendicularVector
Vector3 PerpendicularVector(const Vector3& _src) const {
    int	pos, i;
    float minimumElemants = 1.0F;
    Vector3 tempV3;

    // Find the smallest magnitude axially aligned vector
    std::array<double, 3> vector3Array = _src.ToArray();

    for (pos = 0, i = 0; i < 3; i++) {
        if (std::fabs(vector3Array[i]) < minimumElemants) {
            pos = i;
            minimumElemants = std::fabs(vector3Array[i]);
        }
    }

    tempV3.SetPos(pos, 1.0F);

    // project the point onto the plane defined by src
    tempV3 = tempV3.ProjectPointOnPlane(_src);

    //normalize the result
    tempV3.Normalize();
    return  tempV3;
}




