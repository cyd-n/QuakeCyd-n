//
// Created by quidon on 27-11-2026.
//

#pragma once
#include "gl_model.h"
#include "mathlib.h"
#include "Vector3.h"

class CydnMath {
public:
    static constexpr float PI = 3.14159265358979323846f;
    static constexpr float PI_DIV_180 = (PI / 180.0f);
    static constexpr float TUA = PI * 2;
    const float E = 2.71828182845904523536f;
    const float GOLDEN_RATIO = 1.61803398874989f;
    const float SQRT2 = 1.41421356237f;
    const float SQRT3 = 1.732050807569f;
    const float SQRT5 = 2.23607f;

    const float GRAVITY = 9.81f;
    const int SPEED_OF_LIGHT = 299792458;

    // Deg2Rad, Epsilon, Infinity, NegativeInfinity, Rad2Deg

    // Approximately, CeilToInt, Clamp, Clamp01, ClosestPowerOfTwo, SmoothStep, SmoothDampAngle, Sign,
    // CorrelatedColorTemperatureToRGB, DeltaAngle, FloorToInt, GammaToLinearSpace, SmoothDamp, RoundToInt,
    // InverseLerp, IsPowerOfTwo, Lerp, LerpAngle, LerpUnclamped, LinearToGammaSpace, Repeat, PingPong,
    // MoveTowards, MoveTowardsAngle, NextPowerOfTwo, PerlinNoise

	// I ported the BoxOnPlaneSide to c++ with the help of ChatGPT. Because I dont understand how macros in C works.
	static int BoxOnPlaneSide(Vector3& _mins, Vector3& _maxs, const mplane_t* _plane) {
		if (_plane->type < 3) {
			_mins.Vec3ToVec3_t(_mins);
			if (_plane->dist <= _mins.innerVec_t[_plane->type]) { return 1; }

			_maxs.Vec3ToVec3_t(_maxs);
			if (_plane->dist <= _maxs.innerVec_t[_plane->type]) { return 2; }

			return 3;
		}

		return BoxOnPlaneSide(_mins, _maxs, _plane);
	}
};

