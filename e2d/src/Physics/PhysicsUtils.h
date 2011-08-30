#ifndef AIR2D_PHYSICS_UTILS_H
#define AIR2D_PHYSICS_UTILS_H

#include "PhysicsCommon.h"

namespace air2d {
	namespace physics {

#define ToBox2Vec(VEC) b2Vec2(VEC.x, VEC.y)
#define ToGlmVec(VEC) vec2(VEC.x, VEC.y)
	
	}
}

#endif