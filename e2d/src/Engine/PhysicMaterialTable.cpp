#include <p2d/Common.h>

#include "e2d/Engine/PhysicMaterialTable.h"

namespace e2d {
	namespace engine {
		void PhysicMaterialTable::AddPhysicMaterial(const string_t& materialName, std::auto_ptr<p2d::Material> materialPtr) {
			CGL_CHECK(m_physicMaterialTable.count(materialName) == 0);
			m_physicMaterialTable[materialName] = MaterialPtr(materialPtr.release());
		}

		p2d::Material* PhysicMaterialTable::GetPhysicMaterial(const string_t& materialName) {
			CGL_CHECK(m_physicMaterialTable.count(materialName) != 0);
			return m_physicMaterialTable[materialName].get();
		}

		bool PhysicMaterialTable::HasPhysicMaterial(const string_t& materialName) {
			return m_physicMaterialTable.count(materialName) != 0;
		}
	}
}