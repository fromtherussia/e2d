#include "IRenderable.h"
#include "IMaterial.h"

namespace r2d {
	IRenderable::IRenderable(const IMaterialPtr& pMaterial):
		m_pMaterial(pMaterial),
		m_isRotationOriginSet(false) {
	}

	const IMaterial* IRenderable::GetMaterial() const {
		return m_pMaterial.get();
	}

	void IRenderable::SetRotationOrigin(const vec2& rotationOrigin) {
		m_isRotationOriginSet = true;
		m_rotationOrigin = rotationOrigin;
	}

	vec2 IRenderable::GetRotationOrigin() const {
		return m_rotationOrigin;
	}
}