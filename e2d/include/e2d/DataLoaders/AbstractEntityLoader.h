#ifndef E2D_DATA_LOADERS_ABSTRACT_ENTITY_LOADER_H
#define E2D_DATA_LOADERS_ABSTRACT_ENTITY_LOADER_H

#include "e2d/DataLoaders/IEntityLoader.h"

namespace e2d {
	namespace loaders {
		class AbstractEntityLoader: public IEntityLoader {
		public:
			virtual engine::IEntity* Load(boost::property_tree::ptree& parsedEntity, engine::IResourceController& resourceController, SceneLoader& sceneLoader) const;
		};
	}
}

#endif