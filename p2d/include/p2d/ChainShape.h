#ifndef P2D_CHAIN_SHAPE_H
#define P2D_CHAIN_SHAPE_H

#include "p2d/IShape.h"

namespace p2d {
	class ChainShape: public IShape {
	public:
		ChainShape(const PolygonalChain2d& vertices, Material& attrs);
		virtual ~ChainShape();
		virtual void DebugRender(const DebugRenderer& debugRenderer);
		virtual void GetVertecies(Polygon2d& vertecies);
	private:
		PolygonalChain2d vertices;
		std::auto_ptr<b2ChainShape> chainShapePtr;
	};
}

#endif