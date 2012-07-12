#include <Box2D/Box2D.h>

#include "p2d/DebugRenderer.h"
#include "p2d/Utils.h"

#include "p2d/CircleShape.h"

namespace p2d {
	CircleShape::CircleShape(const Circle& circle, Material& attrs):
		m_circle(circle) {
		m_circleShapePtr = new b2CircleShape;
		m_circleShapePtr->m_radius = circle.GetRadius();
		m_circleShapePtr->m_p = ToBox2dVec(circle.GetOrigin());
		Construct(m_circleShapePtr, attrs);
	}

	CircleShape::~CircleShape() {
		delete m_circleShapePtr;
	}

	void CircleShape::GetVertecies(Polygon2d& vertecies) {
		for (int32 i = 0; i< m_circleShapePtr->GetVertexCount(); ++i) {
			vertecies << ToGlmVec(m_circleShapePtr->GetVertex(i));
		}
	}

	void CircleShape::DebugRender(const DebugRenderer& debugRenderer) {
		debugRenderer.RenderWireCircle(m_circle);
	}
}