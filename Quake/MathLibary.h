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

class MathLib {
public:
    MathLib() = delete; // Make so if you try to insteanced this class he wont do it

    Vector3 vec3_origin = {0,0,0};

    float Deg2Rad(float _degree);
    int ToRoundInteger(float _float); // Og: Q_rint

    // ??

    Vector3 VectorAngles(const vec3_t forward, vec3_t angles);

    void VectorMA (vec3_t veca, float scale, vec3_t vecb, vec3_t vecc);

    void VectorScale (vec3_t in, vec_t scale, vec3_t out);
    int Q_log2(int val);
    // Exit

    fixed16_t Invert24To16(fixed16_t val);
};

#endif

#endif
