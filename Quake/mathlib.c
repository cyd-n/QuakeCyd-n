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
// mathlib.c -- math primitives

#include "quakedef.h"

vec3_t vec3_origin = {0,0,0};


//johnfitz -- removed RotatePointAroundVector() becuase it's no longer used and my compiler fucked it up anyway

/*-----------------------------------------------------------------*/


float	anglemod(float a)
{
#if 0
	if (a >= 0)
		a -= 360*(int)(a/360);
	else
		a += 360*( 1 + (int)(-a/360) );
#endif
	a = (360.0/65536) * ((int)(a*(65536/360.0)) & 65535);
	return a;
}



int Q_log2(int val)
{
	int answer=0;
	while (val>>=1)
		answer++;
	return answer;
}


/*
================
R_ConcatRotations
================
*/
void R_ConcatRotations (float in1[3][3], float in2[3][3], float out[3][3])
{
	out[0][0] = in1[0][0] * in2[0][0] + in1[0][1] * in2[1][0] +
				in1[0][2] * in2[2][0];
	out[0][1] = in1[0][0] * in2[0][1] + in1[0][1] * in2[1][1] +
				in1[0][2] * in2[2][1];
	out[0][2] = in1[0][0] * in2[0][2] + in1[0][1] * in2[1][2] +
				in1[0][2] * in2[2][2];
	out[1][0] = in1[1][0] * in2[0][0] + in1[1][1] * in2[1][0] +
				in1[1][2] * in2[2][0];
	out[1][1] = in1[1][0] * in2[0][1] + in1[1][1] * in2[1][1] +
				in1[1][2] * in2[2][1];
	out[1][2] = in1[1][0] * in2[0][2] + in1[1][1] * in2[1][2] +
				in1[1][2] * in2[2][2];
	out[2][0] = in1[2][0] * in2[0][0] + in1[2][1] * in2[1][0] +
				in1[2][2] * in2[2][0];
	out[2][1] = in1[2][0] * in2[0][1] + in1[2][1] * in2[1][1] +
				in1[2][2] * in2[2][1];
	out[2][2] = in1[2][0] * in2[0][2] + in1[2][1] * in2[1][2] +
				in1[2][2] * in2[2][2];
}


/*
================
R_ConcatTransforms
================
*/
void R_ConcatTransforms (float in1[3][4], float in2[3][4], float out[3][4])
{
	out[0][0] = in1[0][0] * in2[0][0] + in1[0][1] * in2[1][0] +
				in1[0][2] * in2[2][0];
	out[0][1] = in1[0][0] * in2[0][1] + in1[0][1] * in2[1][1] +
				in1[0][2] * in2[2][1];
	out[0][2] = in1[0][0] * in2[0][2] + in1[0][1] * in2[1][2] +
				in1[0][2] * in2[2][2];
	out[0][3] = in1[0][0] * in2[0][3] + in1[0][1] * in2[1][3] +
				in1[0][2] * in2[2][3] + in1[0][3];
	out[1][0] = in1[1][0] * in2[0][0] + in1[1][1] * in2[1][0] +
				in1[1][2] * in2[2][0];
	out[1][1] = in1[1][0] * in2[0][1] + in1[1][1] * in2[1][1] +
				in1[1][2] * in2[2][1];
	out[1][2] = in1[1][0] * in2[0][2] + in1[1][1] * in2[1][2] +
				in1[1][2] * in2[2][2];
	out[1][3] = in1[1][0] * in2[0][3] + in1[1][1] * in2[1][3] +
				in1[1][2] * in2[2][3] + in1[1][3];
	out[2][0] = in1[2][0] * in2[0][0] + in1[2][1] * in2[1][0] +
				in1[2][2] * in2[2][0];
	out[2][1] = in1[2][0] * in2[0][1] + in1[2][1] * in2[1][1] +
				in1[2][2] * in2[2][1];
	out[2][2] = in1[2][0] * in2[0][2] + in1[2][1] * in2[1][2] +
				in1[2][2] * in2[2][2];
	out[2][3] = in1[2][0] * in2[0][3] + in1[2][1] * in2[1][3] +
				in1[2][2] * in2[2][3] + in1[2][3];
}


/*
===================
FloorDivMod

Returns mathematically correct (floor-based) quotient and remainder for
numer and denom, both of which should contain no fractional part. The
quotient must fit in 32 bits.
====================
*/

void FloorDivMod (double numer, double denom, int *quotient,
		int *rem)
{
	int		q, r;
	double	x;

#ifndef PARANOID
	if (denom <= 0.0)
		Sys_Error ("FloorDivMod: bad denominator %f\n", denom);

//	if ((floor(numer) != numer) || (floor(denom) != denom))
//		Sys_Error ("FloorDivMod: non-integer numer or denom %f %f\n",
//				numer, denom);
#endif

	if (numer >= 0.0)
	{

		x = floor(numer / denom);
		q = (int)x;
		r = (int)floor(numer - (x * denom));
	}
	else
	{
	//
	// perform operations with positive values, and fix mod to make floor-based
	//
		x = floor(-numer / denom);
		q = -(int)x;
		r = (int)floor(-numer - (x * denom));
		if (r != 0)
		{
			q--;
			r = (int)denom - r;
		}
	}

	*quotient = q;
	*rem = r;
}


/*
===================
GreatestCommonDivisor
====================
*/
int GreatestCommonDivisor (int i1, int i2)
{
	if (i1 > i2)
	{
		if (i2 == 0)
			return (i1);
		return GreatestCommonDivisor (i2, i1 % i2);
	}
	else
	{
		if (i1 == 0)
			return (i2);
		return GreatestCommonDivisor (i1, i2 % i1);
	}
}


/*
===================
Invert24To16

Inverts an 8.24 value to a 16.16 value
====================
*/

fixed16_t Invert24To16(fixed16_t val)
{
	if (val < 256)
		return (0xFFFFFFFF);

	return (fixed16_t)
			(((double)0x10000 * (double)0x1000000 / (double)val) + 0.5);
}

