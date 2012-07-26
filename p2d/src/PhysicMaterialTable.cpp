#include "p2d/PhysicMaterialTable.h"

namespace p2d {
	void PhysicMaterialTable::AddMaterial(const std::string& materialName, std::auto_ptr<p2d::Material> materialPtr) {
		CGL_CHECK(m_physicMaterialTable.count(materialName) == 0);
		m_physicMaterialTable[materialName] = MaterialPtr(materialPtr.release());
	}

	p2d::Material& PhysicMaterialTable::GetMaterial(const std::string& materialName) {
		CGL_CHECK(m_physicMaterialTable.count(materialName) != 0);
		return *m_physicMaterialTable.at(materialName);
	}

	bool PhysicMaterialTable::HasMaterial(const std::string& materialName) const {
		return m_physicMaterialTable.count(materialName) != 0;
	}
}