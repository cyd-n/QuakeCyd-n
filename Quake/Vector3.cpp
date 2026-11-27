//
// Created by quidon on 27-11-2026.
//

#include "Vector3.h"

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

float Vector3::Magnitude() const {
    Vector3 v = *this;
    return sqrt(Dot(v, v));
}
Vector3 Vector3::Normalize() const {
    float mag = this->Magnitude();
    Vector3	vec = *this;

    if (mag) {
        float iMag = 1/mag;
        vec.x *= iMag;
        vec.y *= iMag;
        vec.z *= iMag;
    }

    return vec;
}
Vector3 Vector3::Inverse() const {
    Vector3 vec3 = Vector3::Zero();
    vec3.x = -vec3.x;
    vec3.y = -vec3.y;
    vec3.z = -vec3.z;

    return  vec3;
}
Vector3 Vector3::MA (float _scale, Vector3 _other) const {
    Vector3 vec3 = Vector3::Zero();
    vec3.x = x + _scale * _other.x;
    vec3.y = y + _scale * _other.y;
    vec3.z = z + _scale * _other.z;

    return vec3;
}
Vector3 Vector3::Perpendicular(Vector3 _src) const {
    Vector3 tempV = Vector3::Zero();
    double minElements = 1.0f;
    int position = 0,  i = 0;

    // find the smallest magnitude axially aligned vector
    for (position = 0, i = 0; i < 3; i++ ) {
        _src.Vec3ToVec3_t(_src);
        if (fabs(_src.innerVec_t[i]) < minElements) {
            position = i;
            minElements = fabs(_src.innerVec_t[i]);
        }
    }

    tempV.Vec3ToVec3_t(tempV);
    tempV.innerVec_t[position] = 1.0F;
    tempV.Vec3_tToVec3(tempV.innerVec_t);

    // project the point onto the plane defined by src
    Vector3 result = ProjectPointOnPlane(tempV, _src);

    // normalize the result
    result.Normalize();
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
Vector3 ProjectPointOnPlane(const Vector3& _p, const Vector3& _normal) {
    Vector3 result = Vector3::Zero();

    float invDenom = 1.0F / Vector3::Dot(_normal, _normal);
    float distance = Vector3::Dot(_normal, _p) * invDenom;

    Vector3 normal = Vector3::Zero();
    normal.x = _normal.x * invDenom;
    normal.y = _normal.y * invDenom;
    normal.z = _normal.z * invDenom;

    result.x = _p.x - distance * normal.x;
    result.y = _p.y - distance * normal.y;
    result.z = _p.z - distance * normal.z;

    return result;
}

//TODO: take right and up vectors to properly set yaw and roll
Vector3 Vector3::Angles(const Vector3& _forward) {
	Vector3 tempV = Vector3::Zero();

	tempV.x = _forward.x;
	tempV.y = _forward.y;
	tempV.z = 0;

	Vector3 angles = Vector3::Zero();
	angles.x = -atan2(_forward.z, tempV.Magnitude()/ CydnMath::PI_DIV_180 );

	angles.x = -atan2(_forward.z, tempV.Magnitude()) / CydnMath::PI_DIV_180; // X is pitch
	angles.y = atan2(_forward.y, _forward.x) / CydnMath::PI_DIV_180; // Y is yaw
	angles.z = 0; // Z is roll
}

std::array<Vector3, 3> Vector3::AnglesTo3Vec3(const Vector3& _angle) {
	std::array<Vector3, 3> vec3Array = {Vector3::Zero(), Vector3::Zero(), Vector3::Zero()};

	Vector3 forward = Vector3::Zero();
	Vector3 right = Vector3::Zero();
	Vector3 up = Vector3::Zero();

	float angle;
	float sineRaw, sinePitch, sineYaw, cosineRaw, cosinePitch, cosineYaw;

	angle = _angle.y * (CydnMath::PI * 2 / 360);
	sineYaw = std::sin(angle);
	cosineYaw = std::cos(angle);

	angle = _angle.x * (CydnMath::PI * 2 / 360);
	sinePitch = std::sin(angle);
	cosinePitch = std::cos(angle);

	angle = _angle.z * (CydnMath::PI * 2 / 360);
	sineRaw = std::sin(angle);
	cosineRaw = std::cos(angle);

	forward.x = cosinePitch * cosineYaw;
	forward.y = cosinePitch * sineYaw;
	forward.z = -sinePitch;
	vec3Array[0] = forward;

	right.x = (-1 * sineRaw * sinePitch * cosineYaw + -1 * cosineRaw * -sineYaw);
	right.y = (-1 * sineRaw * sinePitch * sineYaw + -1 * cosineRaw * cosineYaw );
	right.z = -1 * sineRaw * cosinePitch;
	vec3Array[1] = right;

	up.x = (cosineRaw* sinePitch * cosineYaw + -sineRaw * sineYaw);
	up.y = (cosineRaw* sinePitch * sineYaw + -sineRaw * cosineYaw);
	up.z = cosineRaw* cosinePitch;
	vec3Array[2] = up;

	return vec3Array;
}

void Vector3::Vec3ToVec3_t(const Vector3& _v) {
    innerVec_t[0] = _v.x;
    innerVec_t[1] = _v.y;
    innerVec_t[2] = _v.z;
}
void Vector3::Vec3_tToVec3(const vec3_t& _v) {
    x = _v[0];
    y = _v[1];
    z = _v[2];
}
