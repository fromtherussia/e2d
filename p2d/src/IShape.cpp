#include <Box2D/Box2D.h>

#include "p2d/Utils.h"

#include "p2d/IShape.h"

namespace p2d {
	IShape::IShape():
		m_bodyPtr(NULL) {
	}

	IShape::~IShape() {
		if (m_bodyPtr) {
			m_bodyPtr->DestroyFixture(m_fixturePtr);
		}
		if (m_fixtureDefPtr) {
			delete m_fixtureDefPtr;
		}
	}

	vec2 IShape::GetPosition() const {
		return ToGlmVec(m_bodyPtr->GetPosition());
	}

	float IShape::GetAngle() const {
		return m_bodyPtr->GetAngle();
	}

	bool IShape::AttachToBody(b2Body* body) {
		m_bodyPtr = body;
		m_fixturePtr = body->CreateFixture(m_fixtureDefPtr);
		return true;
	}

	void IShape::Construct(const b2Shape* shape, Material& attrs) {
		m_fixtureDefPtr = new b2FixtureDef();
		m_fixtureDefPtr->shape = shape;
		m_fixtureDefPtr->isSensor = attrs.m_isSensor;
		/*m_fixtureDef.filter.categoryBits = attrs.m_filter.categoryBits;
		m_fixtureDef.filter.maskBits = attrs.m_filter.maskBits;
		m_fixtureDef.filter.groupIndex = attrs.m_filter.groupIndex;*/
		m_fixtureDefPtr->friction = attrs.m_friction;
		m_fixtureDefPtr->restitution = attrs.m_restitution;
		m_fixtureDefPtr->density = attrs.m_density;
	}
}