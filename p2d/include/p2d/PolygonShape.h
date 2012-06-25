#ifndef P2D_POLYGON_SHAPE_H
#define P2D_POLYGON_SHAPE_H

#include "p2d/IShape.h"

namespace p2d {
	class PolygonShape: public IShape {
	public:
		PolygonShape(const Polygon2d& polygon, Material& attrs);
		virtual ~PolygonShape();
		virtual void GetVertecies(Polygon2d& vertecies);
		virtual void DebugRender(const DebugRenderer& debugRenderer);
	
	private:
		Polygon2d m_polygon;
		b2PolygonShape* m_polygonShapePtr;
	};
}

#endif