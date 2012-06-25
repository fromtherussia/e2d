#ifndef E2D_ENGINE_GRAPHIC_MATERIAL_TABLE_H
#define E2D_ENGINE_GRAPHIC_MATERIAL_TABLE_H

#include "e2d/Engine/Common.h"

namespace e2d {
	namespace engine {
		class GraphicMaterialTable {
		public:
			virtual void AddGraphicMaterial(const string_t& materialName, std::auto_ptr<r2d::IMaterial> materialPtr);
			virtual r2d::IMaterial* GetGraphicMaterial(const string_t& materialName);
			virtual bool HasGraphicMaterial(const string_t& materialName);
		private:
			typedef boost::shared_ptr<r2d::IMaterial> IMaterialPtr;
			std::map<string_t, IMaterialPtr> m_graphicMaterialTable;
		};
	}
}

#endif