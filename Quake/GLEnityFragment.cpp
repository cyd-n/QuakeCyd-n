//
// Created by quidon on 28-11-2026.
//

#include "GLEnityFragment.hpp"
#include "Vector3.h"

efrag_t* GLEnityFragment::GetEnityFragment (void) {
    // we could just Hunk_Alloc a single efrag_t and return it, but since
    // the struct is so small (2 pointers) allocate groups of them
    // to avoid wasting too much space on the hunk allocation headers.

    if (cl.free_efrags) {
        efrag_t *enityFragment = cl.free_efrags; // is in render.h
        cl.free_efrags = enityFragment->leafnext; // in cl_main.c
        enityFragment->leafnext = NULL;

        cl.num_efrags++;

        return enityFragment;
    } else {
        int i;

        cl.free_efrags = (efrag_t *) Hunk_AllocName (EXTRA_ENITY_FRAGMENTS * sizeof (efrag_t), "efrags");

        for (i = 0; i < EXTRA_ENITY_FRAGMENTS - 1; i++)
            cl.free_efrags[i].leafnext = &cl.free_efrags[i + 1];

        cl.free_efrags[i].leafnext = NULL;

        // call recursively to get a newly allocated free efrag
        return GetEnityFragment();
    }
}

void GLEnityFragment::SplitEntityOnNode(mnode_t* _node) {
    efrag_t		*ef;
    mplane_t	*splitplane;
    mleaf_t		*leaf;
    int			sides;

    if (_node->contents == CONTENTS_SOLID) { return; }

    // add an EnityFragment if the node is a leaf

    if (_node->contents < 0) {
        if (!pefragtopnode) { pefragtopnode = _node; }

        leaf = (mleaf_t *)_node;

        // grab an efrag off the free list
        ef = GetEnityFragment();
        ef->entity = addent;

        // set the leaf links
        ef->leafnext = leaf->efrags;
        leaf->efrags = ef;

        return;
    }

    // NODE_MIXED

    splitplane = _node->plane;
    sides = CydnMath::BoxOnPlaneSide(min, max, splitplane);

    if (sides == 3){
        // split on this plane
        // if this is the first splitter of this bmodel, remember it
        if (!pefragtopnode)
            pefragtopnode = _node;
    }

    // recurse down the contacted sides
    if (sides & 1) { SplitEntityOnNode (_node->children[0]); }

    if (sides & 2) { SplitEntityOnNode (_node->children[1]); }
}

void GLEnityFragment::CheckEnityFragment(void) {
    if (cls.signon < 2) {
        return; //don't spam when still parsing signon packet full of static ents
    }
    if (cl.num_efrags > 640 && dev_peakstats.efrags <= 640) { Con_DWarning ("%i efrags exceeds standard limit of 640.\n", cl.num_efrags); }

    dev_stats.efrags = cl.num_efrags;
    dev_peakstats.efrags = q_max(cl.num_efrags, dev_peakstats.efrags);
}

void GLEnityFragment::AddEnityFragment(entity_t* _ent) {
    qmodel_t *entmodel;
    float scalefactor;

    if (!_ent->model) { return; }

    addent = _ent;

    pefragtopnode = NULL;

    entmodel = _ent->model;
    scalefactor = ENTSCALE_DECODE(_ent->scale); // need replacing

    // this part is temp fix so that mine vector 3 and old vec3_t can work together
    Vector3 entVec = Vector3::Zero();
    Vector3 entmodelMinVec = Vector3::Zero();
    Vector3 entmodelMaxVec = Vector3::Zero();

    entVec.Vec3_tToVec3(_ent->origin); // now thos the vector3 has the value of the vec3_t
    entmodelMinVec.Vec3_tToVec3(entmodel->mins);
    entmodelMaxVec.Vec3_tToVec3(entmodel->maxs);

    if (scalefactor != 1.0f) {
        min = entVec.MA(scalefactor, entmodelMinVec);
        max = entVec.MA(scalefactor, entmodelMaxVec);
    } else {
        min = entVec - entmodelMinVec;
        max = entVec - entmodelMinVec;
    }

    SplitEntityOnNode(cl.worldmodel->nodes);

    _ent->topnode = pefragtopnode;

    CheckEnityFragment();
}

void GLEnityFragment::StoreEfragsEnityFragmen (efrag_t** _pPEnityFragment) {
    entity_t* pent;
    efrag_t* pEnityFragment;

    while ((pEnityFragment = *_pPEnityFragment) != NULL) {
        pent = pEnityFragment->entity;

        if ((pent->visframe != r_framecount) && (cl_numvisedicts < MAX_VISEDICTS)) {
            cl_visedicts[cl_numvisedicts++] = pent;
            pent->visframe = r_framecount;
        }

        _pPEnityFragment = &pEnityFragment->leafnext;
    }
}


