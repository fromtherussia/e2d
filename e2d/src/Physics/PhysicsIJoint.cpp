#include <Box2D/Box2D.h>

#include "PhysicsUtils.h"
#include "PhysicsWorld.h"
#include "PhysicsPrimitive.h"

#include "PhysicsIJoint.h"

namespace air2d {
	namespace physics {
		// Public

		IJoint::~IJoint() {
			m_world.DestroyJoint(m_pJoint);
		}

		void IJoint::DebugRender(const r2d::IRenderContext& context) {
			Render(context);
		}

		vec2 IJoint::GetAnchorA() {
			return ToGlmVec(m_pJoint->GetAnchorA());
		}

		vec2 IJoint::GetAnchorB() {
			return ToGlmVec(m_pJoint->GetAnchorB());
		}

		// Protected

		IJoint::IJoint(World& world, const b2JointDef& jointDef): 
			m_jointDef(jointDef),
			m_world(*world.m_pWorld) {
		}
		
		void IJoint::Construct() {
			m_pJoint = m_world.CreateJoint(&m_jointDef);
		}

		b2Body* IJoint::GetPrimitiveBody(Primitive& primitive) {
			return primitive.m_pBody;
		}
	}
}