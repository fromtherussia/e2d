#include <Box2D/Box2D.h>

#include "PhysicsUtils.h"
#include "PhysicsIShape.h"

#include "PhysicsPolygonShape.h"

namespace air2d {
	namespace physics {
		// Public

		PolygonShape::PolygonShape(const Polygon2d& polygon, Material& attrs):
			m_polygon(polygon) {
			
			b2Vec2* vertecies = new b2Vec2[polygon.VerteciesCount()];
			const Vertecies& polygonVertecies = polygon.GetVertecies();
			for (size_t vertexNo = 0; vertexNo < polygonVertecies.size(); ++vertexNo) {
				vertecies[vertexNo] = ToBox2Vec(polygonVertecies[vertexNo]);
			}
			
			m_pPolygonShape = new b2PolygonShape;
			m_pPolygonShape->Set(vertecies, polygon.VerteciesCount());
			delete[] vertecies;
			
			Construct(m_pPolygonShape, attrs);
		}
		
		PolygonShape::~PolygonShape() {
			delete m_pPolygonShape;
		}
		
		// Protected

		void PolygonShape::Render(const r2d::IRenderContext& context) const {
			context.RenderWirePolygon(m_polygon);
		}
	}
}