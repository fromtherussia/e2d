#ifndef E2D_DATA_IENTITY_LOADER_H
#define E2D_DATA_IENTITY_LOADER_H

#include "e2d/DataLoaders/Common.h"

namespace e2d {
	namespace loaders {
		class IEntityLoader {
		public:
			virtual std::auto_ptr<engine::IEntity> Load(boost::property_tree::ptree& shapeNode, engine::IResourceController& resourceController, SceneLoader& sceneLoader) const = 0;
		};
	}
}

#endif