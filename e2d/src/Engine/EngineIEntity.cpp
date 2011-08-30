#include "EngineCommon.h"

#include "EngineIEntity.h"

namespace air2d {
	namespace engine {
		// IWithNamedPoints

		void IWithNamedPoints::AddNamedPoint(const string_t& applicationPointName, vec2 point) {
			assert(m_namedPoints.count(applicationPointName) == 0);
			m_namedPoints[applicationPointName] = point;
		}

		vec2 IWithNamedPoints::GetNamedPoint(const string_t& applicationPointName) {
			assert(m_namedPoints.count(applicationPointName) != 0);
			return m_namedPoints[applicationPointName];
		}

		// IEntity
		IEntity::IEntity(EntityType::Type type):
			m_type(type) {
		}
		
		IEntity::~IEntity() {
		}

		EntityType::Type IEntity::GetType() {
			return m_type;
		}

		// IStaticEntity
		IStaticEntity::IStaticEntity() {
		}

		IStaticEntity::~IStaticEntity() {

		}

		// IKinematicEntity
		IKinematicEntity::IKinematicEntity() {
		}

		IKinematicEntity::~IKinematicEntity() {

		}

		// IDynamicEntity
		IDynamicEntity::IDynamicEntity() {
		}
		
		IDynamicEntity::~IDynamicEntity() {
		}
	}
}