#ifndef E2D_DATA_LOADERS_RESOURCE_LOADER_H
#define E2D_DATA_LOADERS_RESOURCE_LOADER_H

#include "e2d/DataLoaders/Common.h"

namespace e2d {
	namespace loaders {
		class ResourceLoader {
		public:
			enum ResourceType {
				GRAPHIC_MATERIAL,
				PHYSIC_MATERIAL,
				TEXTURE,
				ENTITY_PROTOTYPE
			};
			static istream_ptr GetResourceFileStream(const string_t& fileName, ResourceType type);
		};
	}
}

#endif