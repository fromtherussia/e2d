#ifndef E2D_ENGINE_IPOLYGON_DESTRUCTOR_H
#define E2D_ENGINE_IPOLYGON_DESTRUCTOR_H

#include "e2d/Engine/Common.h"

namespace e2d {
	namespace engine {
		class IPolygonDestructor {
		public:
			IPolygonDestructor() {}
			virtual ~IPolygonDestructor() {}
			virtual void Destruct(
				const Polygon2d& sourcePolygon,
				const vec2& destructionPoint,
				const vec2& destructionVector,
				std::vector<Polygon2d>& resultPolygones
			) = 0;
		};
	}
}

#endif