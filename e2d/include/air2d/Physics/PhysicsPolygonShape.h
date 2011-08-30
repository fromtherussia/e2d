#ifndef AIR2D_PHYSICS_POLYGON_SHAPE_H
#define AIR2D_PHYSICS_POLYGON_SHAPE_H

#include "PhysicsCommon.h"

namespace air2d {
	namespace physics {
		class PolygonShape: public IShape {
		public:
			PolygonShape(const Polygon2d& polygon, Material& attrs);
			virtual ~PolygonShape();
		
		private:
			RESTRICT_COPY_CTOR(PolygonShape);
			RESTRICT_ASSIGN_OPERATOR(PolygonShape);

			virtual void Render(const r2d::IRenderContext& context) const;

			Polygon2d m_polygon;
			b2PolygonShape* m_pPolygonShape;
		};
	}
}

#endif