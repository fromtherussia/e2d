#include <Box2D/Box2D.h>

#include "PhysicsUtils.h"
#include "PhysicsIJoint.h"

#include "PhysicsLengthJoint.h"

namespace air2d {
	namespace physics {
		// Public

		LengthJoint::LengthJoint(World& world, Primitive& primitive1, Primitive& primitive2, vec2 anchor1, vec2 anchor2):
			IJoint(world, *m_pDistanceJointDef) {
			m_pDistanceJointDef = new b2DistanceJointDef();
			m_pDistanceJointDef->Initialize(
				GetPrimitiveBody(primitive1),
				GetPrimitiveBody(primitive2),
				ToBox2Vec(anchor1),
				ToBox2Vec(anchor2)
			);
			Construct();
		}

		LengthJoint::~LengthJoint() {
		}

		// Private

		void LengthJoint::Render(const r2d::IRenderContext& context) {
			context.RenderLine(GetAnchorA(), GetAnchorB());
		}
	}
}