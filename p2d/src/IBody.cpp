#include <Box2D/Box2D.h>

#include "p2d/Utils.h"
#include "p2d/World.h"
#include "p2d/IShape.h"

#include "p2d/IBody.h"

namespace p2d {
	IBody::IBody(World& world, Type type, const Material& attributes, const BodyInitialMotion& initialMotion):
		m_world(*world.m_worldPtr),
		m_type(type) {
		b2BodyDef bodyDef;
		switch (type) {
			case ptStatic:
				bodyDef.type = b2_staticBody;
				break;
			case ptKinematic:
				bodyDef.type = b2_kinematicBody;
				break;
			case ptDynamic:
				bodyDef.type = b2_dynamicBody;
				break;
		}
		bodyDef.linearDamping = attributes.m_linearDamping;
		bodyDef.angularDamping = attributes.m_angularDamping;
		bodyDef.allowSleep = attributes.m_allowSleep;
		bodyDef.fixedRotation = attributes.m_fixedRotation;
		bodyDef.bullet = attributes.m_bullet;
		bodyDef.active = attributes.m_active;
		bodyDef.awake = attributes.m_awake;
		bodyDef.position = ToBox2dVec(initialMotion.m_position);
		bodyDef.angle = initialMotion.m_angle;
		bodyDef.linearVelocity = ToBox2dVec(initialMotion.m_linearVelocity);
		bodyDef.angularVelocity = initialMotion.m_angularVelocity;

		m_bodyPtr = m_world.CreateBody(&bodyDef);
	}
	
	IBody::~IBody() {
		m_world.DestroyBody(m_bodyPtr);
	}

	void IBody::AttachShape(IShape* shapePtr) {
		shapePtr->AttachToBody(m_bodyPtr);
	}

	b2Body* IBody::GetBody() {
		return m_bodyPtr;
	}

	vec2 IBody::GetPosition() const {
		return ToGlmVec(m_bodyPtr->GetPosition());
	}

	float IBody::GetAngle() const {
		return m_bodyPtr->GetAngle();
	}

	vec2 IBody::GetLinearVelocity() const {
		return ToGlmVec(m_bodyPtr->GetLinearVelocity());
	}

	float IBody::GetAngularVelocity() const {
		return m_bodyPtr->GetAngularVelocity();
	}

	void IBody::ApplyForce(const vec2& force, const vec2& point) {
		m_bodyPtr->ApplyForce(ToBox2dVec(force), ToBox2dVec(point));
	}

	void IBody::ApplyImpulse(const vec2& force, const vec2& point) {
		m_bodyPtr->ApplyLinearImpulse(ToBox2dVec(force), ToBox2dVec(point));
	}

	void IBody::SetPosition(const vec2& pos) {
		m_bodyPtr->SetTransform(
			ToBox2dVec(pos),
			m_bodyPtr->GetAngle()
		);
	}
	
	void IBody::Move(const vec2& delta) {
		m_bodyPtr->SetTransform(
			m_bodyPtr->GetPosition() + ToBox2dVec(delta),
			m_bodyPtr->GetAngle()
		);
	}
	
	void IBody::SetAngle(float angle) {
		m_bodyPtr->SetTransform(
			m_bodyPtr->GetPosition(),
			angle
		);
	}

	void IBody::Rotate(float delta) {
		m_bodyPtr->SetTransform(
			m_bodyPtr->GetPosition(),
			m_bodyPtr->GetAngle() + delta
		);
	}
}