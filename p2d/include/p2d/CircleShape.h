#ifndef P2D_CIRCLE_SHAPE_H
#define P2D_CIRCLE_SHAPE_H

#include "p2d/IShape.h"

namespace p2d {
	class CircleShape: public IShape {
	public:
		CircleShape(const Circle& circle, Material& attrs);
		virtual ~CircleShape();
		virtual void GetVertecies(Polygon2d& vertecies);
		virtual void DebugRender(const DebugRenderer& debugRenderer);
	
	private:
		Circle m_circle;
		b2CircleShape* m_circleShapePtr;
	};
}

#endif