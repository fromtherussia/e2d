#include "r2d/IMaterial.h"

#include "r2d/IRenderable.h"

namespace r2d {
	IRenderable::IRenderable(IMaterial* materialPtr):
		m_materialPtr(materialPtr),
		m_isRotationOriginSet(false) {
	}

	int IRenderable::GetMaterialId() const {
		return m_materialPtr->GetMaterialId();
	}

	void IRenderable::SetRotationOrigin(const vec2& rotationOrigin) {
		m_isRotationOriginSet = true;
		m_rotationOrigin = rotationOrigin;
	}

	vec2 IRenderable::GetRotationOrigin() const {
		return m_rotationOrigin;
	}
}