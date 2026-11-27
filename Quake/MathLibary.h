/*
Id Software, Inc,John Fitzgibbons, Kristian Duske, QuakeSpasm developers are the devs that work on the project this fork of but this file is made by my inspired on c mathlib in the orginal project
Copyright (C) 2026 Cyd-n

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

I used Claude to help port mathlib to C++. I don't have much experience with
C and C++, so for now I still rely on tools to help me understand the code.
My goal is to rewrite mathlib by hand, without AI, before 2028.

I don't hate AI. But just as some people don't like making pictures with AI
because they see drawing as art, I see code as art. I believe hand-written
code is the most beautiful, not because it is perfect, but because you can
see and feel the programmer in it.
*/

#ifndef MATHLIB_H
#define MATHLIB_H

// MathLib.h

#pragma once
#include <cmath>
#include "quakedef.h"
#include "Vector3.h"

#define PI 3.14159265358979323846
#define PI_DIV_BY180 PI / 180.0

struct mplane_s;

#define	nanmask		(255 << 23)	/* 7F800000 */

#if 0	/* macro is violating strict aliasing rules */
#define	IS_NAN(x)	(((*(int *) (char *) &x) & nanmask) == nanmask)
#else
static inline int IS_NAN (float x) {
    union { float f; int i; } num;
    num.f = x;
    return ((num.i & nanmask) == nanmask);
}
#endif

#define VectorNormalizeFast(_v)\
{\
	union { float f; int i; } _y, _number;\
	_number.f = DotProduct((_v), (_v));\
	if (_number.f != 0.0)\
	{\
		_y.i = 0x5f3759df - (_number.i >> 1);\
		_y.f = _y.f * (1.5f - (_number.f * 0.5f * _y.f * _y.f));\
		VectorScale((_v), _y.f, (_v));\
	}\
}

class MathLib {
public:
    MathLib() = delete; // Make so if you try to insteanced this class he wont do it

    Vector3 vec3_origin = {0,0,0};

    float Deg2Rad(float _degree);

    int ToRoundInteger(float _float); // Og: Q_rint
    int QLog2(int _val);

    float Anglemod(float _a);
};

