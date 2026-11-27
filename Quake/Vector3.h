//
// Created by quidon on 27-11-2026.
//

#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3 {
public:
    double x, y, z;

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

    // magnitude, normalized, sqrtMagnitude, this[int]

    static bool Equals(const Vector3& _a, const Vector3& _b);
    static void Set(const Vector3& _copyFrom, Vector3& _copyTo);

    bool EqualsBySelf(const Vector3& _other) const;
    void SetBySelf(const Vector3& _other);
    char* ToString() const;

    // Angle, ClampMagnitude, Cross, Lerp, Distance, Dot, MoveToWards, LerpUnclamped, Min, Max, OrthoNormalize, ProjectOnPlane, Project, Reflect,
    // RotateToWards, Slerp, Scale, SlerpUnclamped, SmoothDamp


};


#endif //VECTOR3_H
