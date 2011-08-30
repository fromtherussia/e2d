#include <Box2D/Box2D.h>

#include "PhysicsUtils.h"
#include "PhysicsWorld.h"
#include "PhysicsIShape.h"

#include "PhysicsPrimitive.h"

namespace air2d {
	namespace physics {
		// Public

		Primitive::Primitive(World& world, Type type, const PrimitiveAttributes& attrs, const PrimitiveInitialMotion& initialMotion):
			m_world(*world.m_pWorld) {
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
			bodyDef.linearDamping = attrs.m_linearDamping;
			bodyDef.angularDamping = attrs.m_angularDamping;
			bodyDef.allowSleep = attrs.m_allowSleep;
			bodyDef.fixedRotation = attrs.m_fixedRotation;
			bodyDef.bullet = attrs.m_bullet;
			bodyDef.active = attrs.m_active;
			bodyDef.inertiaScale = attrs.m_inertiaScale;
			bodyDef.awake = attrs.m_awake;
			bodyDef.position = ToBox2Vec(initialMotion.m_position);
			bodyDef.angle = initialMotion.m_angle;
			bodyDef.linearVelocity = ToBox2Vec(initialMotion.m_linearVelocity);
			bodyDef.angularVelocity = initialMotion.m_angularVelocity;

			m_pBody = m_world.CreateBody(&bodyDef);
		}
		
		Primitive::~Primitive() {
			m_shapes.clear();
			m_world.DestroyBody(m_pBody);
		}

		Primitive& Primitive::operator <<(IShape* shape) {
			shape->AttachToBody(m_pBody);
			m_shapes.push_back(IShapePtr(shape));
			return *this;
		}

		IShape& Primitive::operator [](uint index) {
			if (index >= m_shapes.size()) {
				throw std::logic_error("index is out of range");
			}
			return *m_shapes[index];
		}

		void Primitive::ApplyForce(vec2 force, vec2 point) {
			m_pBody->ApplyForce(ToBox2Vec(force), ToBox2Vec(point));
		}

		void Primitive::ApplyImpulse(vec2 force, vec2 point) {
			m_pBody->ApplyLinearImpulse(ToBox2Vec(force), ToBox2Vec(point));
		}

		vec2 Primitive::GetPosition() const {
			return ToGlmVec(m_pBody->GetPosition());
		}

		float Primitive::GetAngle() const {
			return m_pBody->GetAngle();
		}

		void Primitive::DebugRender(const r2d::IRenderContext& context) {
			for (size_t shapeNo = 0; shapeNo < m_shapes.size(); ++shapeNo) {
				m_shapes[shapeNo]->DebugRender(context);
			}
		}

		bool Primitive::IsActive() const {
			return false; 
		}

		size_t Primitive::CountShapes() const {
			return m_shapes.size();
		}

	}
}