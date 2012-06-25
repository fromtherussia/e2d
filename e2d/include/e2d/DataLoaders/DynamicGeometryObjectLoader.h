#ifndef E2D_DATA_LOADERS_DYNAMIC_GEOMETRY_OBJECT_LOADER_H
#define E2D_DATA_LOADERS_DYNAMIC_GEOMETRY_OBJECT_LOADER_H

#include "e2d/DataLoaders/IGraphicShapeLoader.h"

namespace e2d {
	namespace loaders {
		class DynamicGeometryObjectLoader: public IGraphicShapeLoader {
		public:
			virtual std::auto_ptr<r2d::IRenderable> Load(boost::property_tree::ptree& shapeNode, engine::IResourceController& resourceController) const;
		};
	}
}

#endif