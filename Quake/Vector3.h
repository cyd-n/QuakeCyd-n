//
// Created by quidon on 27-11-2026.
//

#ifndef VECTOR3_H
#define VECTOR3_H
#include "q_stdinc.h"
#include <cmath>
#include <string>
#include <array>
#include "CydnMath.h"

class Vector3 {
public:
    double x, y, z;
    vec3_t innerVec_t;

    Vector3(double x, double y, double z) : x(x), y(y), z(z) {};

    Vector3 operator+(const Vector3& o) const;
    Vector3 operator-(const Vector3& o) const;
    Vector3 operator*(const Vector3& o) const;
    Vector3 operator/(const Vector3& o) const;

    Vector3& operator+=(const Vector3& o);
    Vector3& operator-=(const Vector3& o);
    Vector3& operator*=(const Vector3& o);
    Vector3& operator/=(const Vector3& o);

    static Vector3 Forward();
    static Vector3 Back();
    static Vector3 Up();
    static Vector3 Down();
    static Vector3 Left();
    static Vector3 Right();

    static Vector3 One();
    static Vector3 Zero();

    // sqrtMagnitude, this[int]
    Vector3 Normalize() const;
    float Magnitude() const;
    Vector3 Inverse() const;
    Vector3 MA(float _scale, Vector3 _other) const;
    Vector3 Perpendicular(Vector3 _src) const;

    static bool Equals(const Vector3& _a, const Vector3& _b);
    static void Set(const Vector3& _copyFrom, Vector3& _copyTo);

    bool EqualsBySelf(const Vector3& _other) const;
    void SetBySelf(const Vector3& _other);
    char* ToString() const;

    // ClampMagnitude, Lerp, MoveToWards, LerpUnclamped, OrthoNormalize, Reflect, Project, Slerp
    // RotateToWards, SlerpUnclamped, SmoothDamp, ProjectOnPlane
    static float Dot(const Vector3& _a, const Vector3& _b);
    static Vector3 Cross(const Vector3& _a, const Vector3& _b);
    static Vector3 Max(const Vector3& _a, const Vector3& _b);
    static Vector3 Min(const Vector3& _a, const Vector3& _b);
    static float Distance(const Vector3& _a, const Vector3& _b);
    static Vector3 Scale(const Vector3& _a, const Vector3& _b);
    static Vector3 Scale(const Vector3& _a, const double& _b);
    static Vector3 ProjectPointOnPlane(const Vector3& _p, const Vector3& _normal);

    static Vector3 Angles (const Vector3& _forward);
    static std::array<Vector3, 3> AnglesTo3Vec3(const Vector3& _angle);

    void Vec3ToVec3_t(const Vector3& _v);
    void Vec3_tToVec3(const vec3_t& _v);
};


#endif //VECTOR3_H
