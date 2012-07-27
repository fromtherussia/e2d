#include "r2d/IMaterial.h"

#include "r2d/IRenderable.h"

namespace r2d {
	IRenderable::IRenderable(IMaterial& material):
		m_material(material),
		m_isRotationOriginSet(false) {
	}

	int IRenderable::GetMaterialId() const {
		return m_material.GetMaterialId();
	}

	void IRenderable::SetRotationOrigin(const vec2& rotationOrigin) {
		m_isRotationOriginSet = true;
		m_rotationOrigin = rotationOrigin;
	}

	vec2 IRenderable::GetRotationOrigin() const {
		return m_rotationOrigin;
	}
}