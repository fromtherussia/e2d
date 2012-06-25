#ifndef E2D_ENGINE_IRESOURCE_CONTROLLER_H
#define E2D_ENGINE_IRESOURCE_CONTROLLER_H

#include "e2d/Engine/Common.h"

namespace e2d {
	namespace engine {
		class IResourceController {
		public:
			//virtual IEntityFactory* GetEntitiesFactory() = 0;
			virtual r2d::IFactory& GetGraphicObjectsFactory() = 0;
			virtual GraphicMaterialTable& GetGraphicMaterialTable() = 0;
			virtual PhysicMaterialTable& GetPhysicMaterialTable() = 0;
		};
	}
}

#endif