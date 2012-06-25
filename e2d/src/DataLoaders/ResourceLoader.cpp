#include "e2d/DataLoaders/ResourceLoader.h"

namespace e2d {
	namespace loaders {
		istream_ptr ResourceLoader::GetResourceFileStream(const string_t& fileName, ResourceType type) {
			istream_ptr resourceInputStreamPtr(new std::ifstream(fileName.c_str()));
			return resourceInputStreamPtr;
		}
	}
}