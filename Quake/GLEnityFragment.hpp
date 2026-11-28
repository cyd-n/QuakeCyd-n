/*
Copyright (C) 1996-2001 Id Software, Inc.
Copyright (C) 2002-2009 John Fitzgibbons and others
Copyright (C) 2010-2014 QuakeSpasm developers
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

===============================================================================

                    ENTITY FRAGMENT FUNCTIONS

ericw -- GLQuake only uses efrags for static entities, and they're never
removed, so I trimmed out unused functionality and fields in efrag_t.

Now, efrags are just a linked list for each leaf of the static
entities that touch that leaf. The efrags are hunk-allocated so there is no
fixed limit.

This is inspired by MH's tutorial, and code from RMQEngine.
http://forums.insideqc.com/viewtopic.php?t=1930

===============================================================================
*/
# pragma once
#include "quakedef.h"
#include "CydnMath.h"

class Vector3;

class GLEnityFragment {
    static constexpr int EXTRA_ENITY_FRAGMENTS = 128;

public:
    static mnode_t	*pefragtopnode; // is in gl_model.h
    static Vector3 min, max;
    static entity_t	*addent; // is in render.h

    // based on RMQEngine
    static efrag_t *GetEnityFragment (void);
    static void CheckEnityFragment(void);
    static void AddEnityFragment(entity_t* _ent);

    static void SplitEntityOnNode(mnode_t* _node);
    static void StoreEfragsEnityFragmen (efrag_t** _ppenityFragment);
};

