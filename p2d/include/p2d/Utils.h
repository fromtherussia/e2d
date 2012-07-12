#ifndef P2D_UTILS_H
#define P2D_UTILS_H

#include "p2d/Common.h"

namespace p2d {
	#define ToBox2dVec(VEC) b2Vec2(VEC.x, VEC.y)
	#define ToGlmVec(VEC) vec2(VEC.x, VEC.y)

	inline b2BodyType ToBox2dBodyType(BodyKind::Kind kind) {
		switch (kind) {
		case BodyKind::bkStatic:
			return b2_staticBody;
		case BodyKind::bkKinematic:
			return b2_kinematicBody;
		case BodyKind::bkDynamic:
			return b2_dynamicBody;
		default:
			CGL_CHECK(false);
		}

		return b2_staticBody;
	}

	inline BodyKind::Kind ToBodyKind(b2BodyType type) {
		switch (type) {
		case b2_staticBody:
			return BodyKind::bkStatic;
		case b2_kinematicBody:
			return BodyKind::bkKinematic;
		case b2_dynamicBody:
			return BodyKind::bkDynamic;
		default:
			CGL_CHECK(false);
		}

		return BodyKind::bkStatic;
	}
}

#endif