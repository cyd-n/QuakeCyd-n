#include "Vector3.h"
#include <cmath>
#include <cstdint

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

Vector3 Vector3::Cross (const Vector3 _other) {
    Vector3 result;
    result.x = y * _other.z - z * _other.y;
    result.y = z * _other.x - x * _other.z;
    result.z = x * _other.y - y * _other.x;
    return result;
}

void Vector3::TurnVector(const Vector3& _axis, uint8_t _angle) {
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
