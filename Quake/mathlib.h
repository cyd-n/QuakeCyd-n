/*
Copyright (C) 1996-2001 Id Software, Inc.
Copyright (C) 2002-2009 John Fitzgibbons and others
Copyright (C) 2007-2008 Kristian Duske
Copyright (C) 2010-2014 QuakeSpasm developers

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

*/

#ifndef __MATHLIB_H
#define __MATHLIB_H

// mathlib.h

#include <math.h>

#define DEG2RAD(a)		((a) * M_PI_DIV_180)

struct mplane_s;

extern vec3_t vec3_origin;

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

#define Q_rint(x) ((x) > 0 ? (int)((x) + 0.5) : (int)((x) - 0.5)) //johnfitz -- from joequake

//johnfitz -- courtesy of lordhavoc
// QuakeSpasm: To avoid strict aliasing violations, use a float/int union instead of type punning.
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

int Q_log2(int val);

void R_ConcatRotations (float in1[3][3], float in2[3][3], float out[3][3]);
void R_ConcatTransforms (float in1[3][4], float in2[3][4], float out[3][4]);

void FloorDivMod (double numer, double denom, int *quotient,
		int *rem);
fixed16_t Invert24To16(fixed16_t val);
int GreatestCommonDivisor (int i1, int i2);

float	anglemod(float a);




