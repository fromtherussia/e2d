#include <Box2D/Box2D.h>

#include "p2d/Utils.h"

#include "p2d/LengthJoint.h"

namespace p2d {
	LengthJoint::LengthJoint(World& world, IBody& primitive1, IBody& primitive2, const vec2& anchor1, const vec2& anchor2):
		IJoint(world) {
			
		b2DistanceJointDef distanceJointDef;
		distanceJointDef.Initialize(
			GetPrimitiveBody(primitive1),
			GetPrimitiveBody(primitive2),
			ToBox2dVec(anchor1),
			ToBox2dVec(anchor2)
		);
		Construct(distanceJointDef);
	}

	LengthJoint::~LengthJoint() {
	}
}