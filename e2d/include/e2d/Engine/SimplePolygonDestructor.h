#ifndef E2D_ENGINE_SIMPLE_POLYGON_DESTRUCTOR_H
#define E2D_ENGINE_SIMPLE_POLYGON_DESTRUCTOR_H

#include "e2d/Engine/IPolygonDestructor.h"

namespace e2d {
	namespace engine {
		class SimplePolygonDestructor: public IPolygonDestructor {
		public:
			virtual void Destruct(
				const Polygon2d& sourcePolygon,
				const vec2& destructionPoint,
				const vec2& destructionVector,
				std::vector<Polygon2d>& resultPolygones
			);
		};
	}
}

#endif