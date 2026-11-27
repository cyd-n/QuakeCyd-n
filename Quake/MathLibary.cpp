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

float MathLib::Anglemod(float _a) {
#if 0
    if (_a >= 0) { _a -= 360*(int)(_a/360); }
    else { _a += 360*( 1 + (int)(-_a/360) ); }
#endif
    _a = (360.0/65536) * ((int)(_a*(65536/360.0)) & 65535);
    return _a;
}
