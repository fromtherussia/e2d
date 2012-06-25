#ifndef E2D_DATA_IPHYSIC_SHAPE_LOADER_H
#define E2D_DATA_IPHYSIC_SHAPE_LOADER_H

#include "e2d/DataLoaders/Common.h"

namespace e2d {
	namespace loaders {
		class IPhysicShapeLoader {
		public:
			virtual std::auto_ptr<p2d::IShape> Load(boost::property_tree::ptree& shapeNode, engine::IResourceController& resourceController) const = 0;
		};
		DEFPTR(IPhysicShapeLoader);
	}
}

#endif