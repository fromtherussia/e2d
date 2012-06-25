#include "e2d/Engine/IEntity.h"

namespace e2d {
	namespace engine {
		void IPhysicEntity::AddNamedPoint(const string_t& applicationPointName, const vec2& point) {
			CGL_CHECK(m_namedPoints.count(applicationPointName) == 0);
			m_namedPoints[applicationPointName] = point;
		}

		vec2 IPhysicEntity::GetNamedPoint(const string_t& applicationPointName) {
			CGL_CHECK(m_namedPoints.count(applicationPointName) != 0);
			return m_namedPoints[applicationPointName];
		}
	}
}