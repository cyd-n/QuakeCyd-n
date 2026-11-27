//
// Created by quidon on 27-11-2026.
//

#include "Vector3.h"

#include <cmath>
#include <string>
#include <bits/valarray_after.h>

Vector3 Vector3::operator+(const Vector3 &o) const {
    new Vector3(x + o.x, y + o.y, z + o.z);
}
Vector3 Vector3::operator-(const Vector3 &o) const {
    new Vector3(x - o.x, y - o.y, z - o.z);
}
Vector3 Vector3::operator*(const Vector3 &o) const {
    new Vector3(x * o.x, y * o.y, z * o.z);
}
Vector3 Vector3::operator/(const Vector3 &o) const {
    new Vector3(((x != 0) ? x : 1) / ((o.x != 0) ? o.x : 1), ((y != 0) ? y : 1) / ((o.y != 0) ?o.y : 1), ((z != 0) ? z : 1) / ((o.z != 0) ? o.z : 1));
}

Vector3& Vector3::operator+=(const Vector3& o) {
    x += o.x;
    y += o.y;
    z += o.z;
    return *this;
}
Vector3& Vector3::operator-=(const Vector3& o) {
    x -= o.x;
    y -= o.y;
    z -= o.z;
    return *this;
}
Vector3& Vector3::operator*=(const Vector3& o) {
    x *= o.x;
    y *= o.y;
    z *= o.z;
    return *this;
}
Vector3& Vector3::operator/=(const Vector3& o) {
    x = (x != 0) ? x : 1;
    y = (y != 0) ? y : 1;
    z = (z != 0) ? z : 1;

    x /= (o.x != 0) ? o.x : 1;
    y /= (o.y != 0) ? o.y : 1;
    z /= (o.z != 0) ? o.z : 1;
    return *this;
}

Vector3 Vector3::Forward() { return Vector3(0, 0, 1); }
Vector3 Vector3::Back() { return Vector3(0, 0, -1); }
Vector3 Vector3::Up() { return Vector3(0, 1, 0); }
Vector3 Vector3::Down() { return Vector3(0, -1, 0); }
Vector3 Vector3::Right() { return Vector3(1, 0, 0); }
Vector3 Vector3::Left() { return Vector3(-1, 0, 0); }

Vector3 Vector3::Zero() { return Vector3(0, 0, 0); }
Vector3 Vector3::One() { return Vector3(1, 1, 1); }

float Vector3::Magnitude() {
    Vector3& v = *this;
    return sqrt(DotBySelf(v));
}

// need a == to
bool Vector3::Equals(const Vector3& _a, const Vector3& _b) {
    if (_a.x == _b.x && _a.y == _b.y && _a.z == _b.z) {
        return true;
    } else {
        return false;
    }
}
void Vector3::Set(const Vector3& _copyFrom, Vector3& _copyTo) {
    _copyTo = _copyFrom;
}

bool Vector3::EqualsBySelf(const Vector3& _other) const {
    if (x == _other.x && y == _other.y && z == _other.z) {
        return true;
    } else {
        return false;
    }
}
void Vector3::SetBySelf(const Vector3& _other) {
    x = _other.x;
    y = _other.y;
    z = _other.z;
}
char* Vector3::ToString() const {
    std::string returnString = "new";
    returnString = "X:" + std::to_string(x) + ",\n Y:" + std::to_string(y) + ",\n Z:" + std::to_string(z);
    return (char*) returnString.c_str();
}

float Vector3::Dot(const Vector3& _a, const Vector3& _b) {
    return _a.x * _b.x + _a.y * _b.y + _a.z * _b.z;
}
Vector3 Vector3::Cross (const Vector3& _a, const Vector3& _b) {
    Vector3 result = Vector3::Zero();
    result.x = _a.y * _b.z - _a.z * _b.y;
    result.y = _a.z * _b.x - _a.x * _b.z;
    result.z = _a.x * _b.y - _a.y * _b.x;
    return result;
}
Vector3 Vector3::Max (const Vector3& _a, const Vector3& _b) {
    Vector3 result = Vector3::Zero();
    result.x = (_a.x > _b.x) ? _a.x : _b.x;
    result.y = (_a.y > _b.y) ? _a.y : _b.y;
    result.z = (_a.z > _b.z) ? _a.z : _b.z;

    return result;
}
Vector3 Vector3::Min (const Vector3& _a, const Vector3& _b) {
    Vector3 result = Vector3::Zero();
    result.x = (_a.x < _b.x) ? _a.x : _b.x;
    result.y = (_a.y < _b.y) ? _a.y : _b.y;
    result.z = (_a.z < _b.z) ? _a.z : _b.z;

    return result;
}
float Vector3::Distance(const Vector3& _a, const Vector3& _b) {
    double distanceX = _a.x - _b.x;
    double distanceY = _a.y - _b.y;
    double distanceZ = _a.z - _b.z;

    distanceX = sqrt(distanceX);
    distanceY = sqrt(distanceY);
    distanceZ = sqrt(distanceZ);

    return distanceX + distanceY + distanceZ;
}
Vector3 Vector3::Scale(const Vector3& _a, const Vector3& _b) {
    Vector3 result = Vector3::Zero();
    result.x = _a.x * _b.x;
    result.y = _a.y * _b.y;
    result.z = _a.z * _b.z;

    return result;
}
Vector3 Vector3::Scale(const Vector3& _a, const double& _b) {
    Vector3 result = Vector3::Zero();
    result.x = _a.x * _b;
    result.y = _a.y * _b;
    result.z = _a.z * _b;

    return result;
}