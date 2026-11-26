#ifndef VECTOR3_H
#define VECTOR3_H

#pragma once
#include <cstdlib>

#include "q_stdinc.h"

class Vector3 {
public:
    double x, y, z;

    Vector3(double x = 0.0f, double y = 0.0f, double z = 0.0f);

    float Dot(const Vector3& _other) const;
    double DoublePrecisionDot(const Vector3& _other) const;
    int IntPrecisionDot(const Vector3& _other) const;

    bool Compare(const Vector3& _other) const;

    Vector3 Add(const Vector3& _other) const;
    Vector3 Add(const double& _other) const;
    Vector3 Subtract(const Vector3& _other) const;
    Vector3 Subtract(const double& _other) const;
    Vector3 Multiply(const Vector3& _other) const;
    Vector3 Multiply(const double& _other) const;
    Vector3 Divide(const Vector3& _other) const;
    Vector3 Divide(const double& _other) const;

    Vector3 VectorMultiplyAdd (const Vector3& _scale, const Vector3& _other) const;
    Vector3 VectorMultiplyAdd (const double& _scale, const Vector3& _other) const;



    void Scale (const Vector3& _scale);
    void Scale (const double& _scale);

    Vector3 Cross (const Vector3 _other);

    void Turn(const Vector3& _axis, uint8_t _angle);
    void Angles();

    void Inverse();

    float Magnitude() const;
    void Normalize();
};

#endif