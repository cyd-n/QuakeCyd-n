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
#include "MathLibary.h"

#include "MathLib.h"

float MathLib::Deg2Rad(float _degree) { return _degree *  PI_DIV_BY180; }

// In 1998 they use Q_rint because round did not exist, I built a wrap func around round to make sure only classes use MathLib can use it
int MathLib::ToRoundInteger(float _float) { // Og: Q_rint
    return std::round(_float);
}

// I did not change anything of th eog code here i dont unstand what happens
int MathLib::QLog2(int _val) {
    int answer = 0;

    while (val >>= 1) { answer++; }

    return answer;
}

// Code of the old devs, I dont really understand this. --Cyd-n
fixed16_t MathLib::Invert24To16(fixed16_t val) {
    if (val < 256) { return (0xFFFFFFFF); }

    return (fixed16_t)(((double)0x10000 * (double)0x1000000 / (double)val) + 0.5);
}