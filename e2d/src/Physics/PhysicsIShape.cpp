#include <Box2D/Box2D.h>

#include "PhysicsUtils.h"

#include "PhysicsIShape.h"

namespace air2d {
	namespace physics {
		// Public

		IShape::IShape():
			m_pBody(NULL) {
		}

		IShape::~IShape() {
			if (m_pBody) {
				m_pBody->DestroyFixture(m_pFixture);
			}
		}

		vec2 IShape::GetPosition() const {
			return ToGlmVec(m_pBody->GetPosition());
		}

		float IShape::GetAngle() const {
			return m_pBody->GetAngle();
		}

		void IShape::DebugRender(const r2d::IRenderContext& context) const {
			context.SetWorldTransform(GetPosition(), GetAngle());
			context.RenderWorldAxises(GetPosition(), GetAngle());
			Render(context);
			context.ResetWorldTransform();
		}
		
		// Private

		bool IShape::AttachToBody(b2Body* body) {
			m_pBody = body;
			m_pFixture = body->CreateFixture(&m_fixtureDef);
			return true;
		}

		void IShape::Construct(const b2Shape* shape, Material& attrs) {
			m_fixtureDef.shape = shape;
			m_fixtureDef.isSensor = attrs.m_isSensor;
			/*m_fixtureDef.filter.categoryBits = attrs.m_filter.categoryBits;
			m_fixtureDef.filter.maskBits = attrs.m_filter.maskBits;
			m_fixtureDef.filter.groupIndex = attrs.m_filter.groupIndex;*/
			m_fixtureDef.friction = attrs.m_friction;
			m_fixtureDef.restitution = attrs.m_restitution;
			m_fixtureDef.density = attrs.m_density;
		}
	}
}