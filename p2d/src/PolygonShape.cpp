#include <Box2D/Box2D.h>

#include "p2d/DebugRenderer.h"
#include "p2d/Utils.h"
#include "p2d/IShape.h"

#include "p2d/PolygonShape.h"

namespace p2d {
	PolygonShape::PolygonShape(const Polygon2d& polygon, Material& attrs):
		m_polygon(polygon) {
		
		b2Vec2* vertecies = new b2Vec2[polygon.VerteciesCount()];
		const Vertecies& polygonVertecies = polygon.GetVertecies();
		for (size_t vertexNo = 0; vertexNo < polygonVertecies.size(); ++vertexNo) {
			vertecies[vertexNo] = ToBox2Vec(polygonVertecies[vertexNo]);
		}
		
		m_polygonShapePtr = new b2PolygonShape();
		m_polygonShapePtr->Set(vertecies, polygon.VerteciesCount());
		delete[] vertecies;
		
		Construct(m_polygonShapePtr, attrs);
	}
	
	PolygonShape::~PolygonShape() {
		delete m_polygonShapePtr;
	}

	void PolygonShape::GetVertecies(Polygon2d& vertecies) {
		for (int32 i = 0; i< m_polygonShapePtr->GetVertexCount(); ++i) {
			vertecies << ToGlmVec(m_polygonShapePtr->GetVertex(i));
		}
	}

	void PolygonShape::DebugRender(const DebugRenderer& debugRenderer) {
		debugRenderer.RenderWirePolygon(m_polygon);
	}
}