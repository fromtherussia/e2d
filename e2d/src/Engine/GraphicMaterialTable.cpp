#include <r2d/IMaterial.h>

#include "e2d/Engine/GraphicMaterialTable.h"

namespace e2d {
	namespace engine {
		void GraphicMaterialTable::AddGraphicMaterial(const string_t& materialName, std::auto_ptr<r2d::IMaterial> materialPtr) {
			CGL_CHECK(m_graphicMaterialTable.count(materialName) == 0);
			m_graphicMaterialTable[materialName] = IMaterialPtr(materialPtr.release());
		}

		r2d::IMaterial& GraphicMaterialTable::GetGraphicMaterial(const string_t& materialName) {
			CGL_CHECK(m_graphicMaterialTable.count(materialName) != 0);
			return *m_graphicMaterialTable[materialName];
		}

		bool GraphicMaterialTable::HasGraphicMaterial(const string_t& materialName) {
			return m_graphicMaterialTable.count(materialName) != 0;
		}
	}
}