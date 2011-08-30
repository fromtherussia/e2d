#ifndef AIR2D_DATA_LOADERS_COMMON_H
#define AIR2D_DATA_LOADERS_COMMON_H

#include <rapidxml/rapidxml.hpp>
#include <cgl/MathTypes.h>

namespace e2d {
	namespace engine {
		PREDECL_CLASS_WITH_PTR(IEntity);
	}
	namespace physics {
		PREDECL_CLASS_WITH_PTR(IShape);
	}
}

namespace r2d {
	PREDECL_CLASS_WITH_PTR(IRenderable);
}

#endif