#include <Box2D/Box2D.h>

#include "p2d/Utils.h"

#include "p2d/PulleyJoint.h"

namespace p2d {
	PulleyJoint::PulleyJoint(World& world, IBody& primitive1, IBody& primitive2, const vec2& anchor1, const vec2& anchor2, float raito, float minLenght, float maxLength):
		IJoint(world) {

		b2PulleyJointDef pulleyJointDef;
		/*pulleyJointDef.Initialize(
			GetPrimitiveBody(primitive1),
			GetPrimitiveBody(primitive2),
			ToBox2Vec(anchor1),
			ToBox2Vec(anchor2)
		);*/
		Construct(pulleyJointDef);
	}

	PulleyJoint::~PulleyJoint() {
	}
}