#include <Box2D/Box2D.h>

#include "p2d/DebugRenderer.h"
#include "p2d/Utils.h"
#include "p2d/World.h"
#include "p2d/IBody.h"
#include "p2d/CompositeBody.h"

#include "p2d/IJoint.h"

namespace p2d {
	IJoint::IJoint(World& world):		
		m_world(*world.m_worldPtr) {
	}

	IJoint::~IJoint() {
		m_world.DestroyJoint(m_jointPtr);
	}

	vec2 IJoint::GetAnchorA() {
		return ToGlmVec(m_jointPtr->GetAnchorA());
	}

	vec2 IJoint::GetAnchorB() {
		return ToGlmVec(m_jointPtr->GetAnchorB());
	}

	void IJoint::DebugRender(const DebugRenderer& debugRenderer) {
		debugRenderer.RenderLine(GetAnchorA(), GetAnchorB(), JOINT_COLOR_RGB);
	}

	void IJoint::Construct(const b2JointDef& jointDefPtr) {
		m_jointPtr = m_world.CreateJoint(&jointDefPtr);
	}

	b2Body* IJoint::GetPrimitiveBody(IBody& primitive) {
		return primitive.GetBody();
	}
}