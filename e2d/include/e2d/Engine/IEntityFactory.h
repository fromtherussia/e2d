#ifndef E2D_ENGINE_IENTITY_FACTORY_H
#define E2D_ENGINE_IENTITY_FACTORY_H

#include "e2d/Engine/Common.h"

namespace e2d {
	namespace engine {
		class IEntityFactory {
		public:
			virtual ComplexPhysicEntity* CreateComplexPhysicEntity(const vec2& initialPos = vec2(), p2d::IBody::Type type = p2d::IBody::ptStatic, const string_t& primitiveMaterialName = string_t("")) = 0;
		};
	}
}

#endif