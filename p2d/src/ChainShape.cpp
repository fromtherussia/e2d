#include <Box2D/Box2D.h>

#include "p2d/DebugRenderer.h"
#include "p2d/Utils.h"

#include "p2d/ChainShape.h"

namespace p2d {
	ChainShape::ChainShape(const PolygonalChain2d& vertices, Material& attrs):
		chainShapePtr(new b2ChainShape()),
		vertices(vertices) {
		CGL_CHECK(vertices.VerteciesCount() > 0);

		b2Vec2* b2Vertices = new b2Vec2[vertices.VerteciesCount()];

		for (size_t i = 0; i < vertices.VerteciesCount(); ++i) {
			b2Vertices[i] = ToBox2dVec(vertices[i]);
		}

		//chainShapePtr->SetPrevVertex(b2Vertices[0]);
		//chainShapePtr->SetNextVertex(b2Vertices[vertices.size() - 1]);
		chainShapePtr->CreateChain(b2Vertices, vertices.VerteciesCount());
		delete[] b2Vertices;

		Construct(chainShapePtr.get(), attrs);
	}

	ChainShape::~ChainShape() {
	}

	void ChainShape::GetVertecies(Polygon2d& vertecies) {
		//vertecies = this->vertices;
	}

	void ChainShape::DebugRender(const DebugRenderer& debugRenderer) {
		debugRenderer.RenderPolygonalChain(vertices);
	}
}