#ifndef E2D_ENGINE_PHYSIC_MATERIAL_TABLE_H
#define E2D_ENGINE_PHYSIC_MATERIAL_TABLE_H

#include "e2d/Engine/Common.h"

namespace e2d {
	namespace engine {
		class PhysicMaterialTable {
		public:
			virtual void AddPhysicMaterial(const string_t& materialName, std::auto_ptr<p2d::Material> materialPtr);
			virtual p2d::Material& GetPhysicMaterial(const string_t& materialName);
			virtual bool HasPhysicMaterial(const string_t& materialName);
		private:
			typedef boost::shared_ptr<p2d::Material> MaterialPtr;
			std::map<string_t, MaterialPtr> m_physicMaterialTable;
		};
	}
}

#endif