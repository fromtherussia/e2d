#include <Box2D/Box2D.h>

#include "PhysicsUtils.h"
#include "PhysicsIShape.h"

#include "PhysicsCircleShape.h"

namespace air2d {
	namespace physics {
		// Public
		
		CircleShape::CircleShape(const Circle& circle, Material& attrs):
			m_circle(circle) {
			m_pCircleShape = new b2CircleShape;
			m_pCircleShape->m_radius = circle.GetRadius();
			m_pCircleShape->m_p = ToBox2Vec(circle.GetOrigin());
			Construct(m_pCircleShape, attrs);
		}

		CircleShape::~CircleShape() {
			delete m_pCircleShape;
		}
		
		// Private

		void CircleShape::Render(const r2d::IRenderContext& context) const {
			context.RenderWireCircle(m_circle);
		}
	}
}