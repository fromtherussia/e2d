#ifndef E2D_DATA_IGRAPHIC_SHAPE_LOADER_H
#define E2D_DATA_IGRAPHIC_SHAPE_LOADER_H

#include "e2d/DataLoaders/Common.h"

namespace e2d {
	namespace loaders {
		class IGraphicShapeLoader {
		public:
			virtual std::auto_ptr<r2d::IRenderable> Load(boost::property_tree::ptree& shapeNode, engine::IResourceController& resourceController) const = 0;
		};
	}
}

#endif