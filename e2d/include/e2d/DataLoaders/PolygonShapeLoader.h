#ifndef E2D_DATA_LOADERS_POLYGON_SHAPE_LOADER_H
#define E2D_DATA_LOADERS_POLYGON_SHAPE_LOADER_H

#include "e2d/DataLoaders/IPhysicShapeLoader.h"

namespace e2d {
	namespace loaders {
		class PolygonShapeLoader: public IPhysicShapeLoader {
		public:
			virtual std::auto_ptr<p2d::IShape> Load(boost::property_tree::ptree& shapeNode, engine::IResourceController& resourceController) const;
		};
	}
}

#endif