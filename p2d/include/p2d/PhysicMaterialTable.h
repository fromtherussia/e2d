#ifndef P2D_PHYSIC_MATERIAL_TABLE_H
#define P2D_PHYSIC_MATERIAL_TABLE_H

#include "p2d/Common.h"

namespace p2d {
	class PhysicMaterialTable {
	public:
		void AddMaterial(const std::string& materialName, std::auto_ptr<p2d::Material> materialPtr);
		p2d::Material& GetMaterial(const std::string& materialName);
		bool HasMaterial(const std::string& materialName) const;
	private:
		typedef boost::shared_ptr<p2d::Material> MaterialPtr;
		std::map<std::string, MaterialPtr> m_physicMaterialTable;
	};
}

#endif