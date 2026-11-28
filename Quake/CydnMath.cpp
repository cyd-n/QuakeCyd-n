
#include "Vector3.h"
#include "CydnMath.h"

int CydnMath::BoxOnPlaneSide(Vector3& _mins, Vector3& _maxs, const mplane_t* _plane) {
    if (_plane->type < 3) {
        _mins.Vec3ToVec3_t(_mins);
        if (_plane->dist <= _mins.innerVec_t[_plane->type]) { return 1; }

        _maxs.Vec3ToVec3_t(_maxs);
        if (_plane->dist <= _maxs.innerVec_t[_plane->type]) { return 2; }

        return 3;
    }

    return BoxOnPlaneSide(_mins, _maxs, _plane);
}