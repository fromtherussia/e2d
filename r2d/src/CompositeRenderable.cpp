#include "r2d/IRenderable.h"
#include "r2d/IRenderContext.h"

#include "r2d/CompositeRenderable.h"

namespace r2d {
	CompositeRenderable::CompositeRenderable(IRenderContext& renderContext, IMaterial* materialPtr):
		m_renderContext(renderContext),
		IRenderable(materialPtr) {
	}

	CompositeRenderable::~CompositeRenderable() {
	}

	CompositeRenderable& CompositeRenderable::AddRenderable(std::auto_ptr<IRenderable> renderablePtr, vec2 offset) {
		IRenderable* tmpRenderablePtr = renderablePtr.release();
		renderablePtr->SetPosition(offset);
		m_renderableObjects.push_back(tmpRenderablePtr);
		m_renderableObjectsOffsets.push_back(offset);
		return *this;
	}

	IRenderable& CompositeRenderable::operator [] (uint index) {
		if (index >= m_renderableObjects.size()) {
			throw std::logic_error("index is out of range");
		}
		return m_renderableObjects[index];
	}

	void CompositeRenderable::RemoveRenderables() {
		m_renderableObjects.clear();
	}
	
	void CompositeRenderable::SetTransformations(const vec2& position, float angle) {
		m_position = position;
		m_angle = angle;
		for (size_t i = 0; i < m_renderableObjects.size(); ++i) {
			m_renderableObjects[i].SetRotationOrigin(m_position);
			m_renderableObjects[i].SetTransformations(position + m_renderableObjectsOffsets[i], angle);
		}
	}

	void CompositeRenderable::SetPosition(const vec2& position) {
		m_position = position;
		for (size_t i = 0; i < m_renderableObjects.size(); ++i) {
			m_renderableObjects[i].SetRotationOrigin(m_position);
			m_renderableObjects[i].SetPosition(position + m_renderableObjectsOffsets[i]);
		}
	}

	vec2 CompositeRenderable::GetPosition() const {
		return m_position;
	}

	void CompositeRenderable::SetRotation(float angle) {
		m_angle = angle;
		for (size_t i = 0; i < m_renderableObjects.size(); ++i) {
			m_renderableObjects[i].SetRotationOrigin(m_position);
			m_renderableObjects[i].SetRotation(angle);
		}
	}

	float CompositeRenderable::GetRotation() const {
		return m_angle;
	}

	void CompositeRenderable::ResetTransformations() {
		m_angle = 0.0f;
		m_position = vec2();
		for (size_t i = 0; i < m_renderableObjects.size(); ++i) {
			m_renderableObjects[i].ResetTransformations();
		}
	}
	
	Rect CompositeRenderable::GetBoundingRect() const {
		return Rect();
	}

	void CompositeRenderable::AddToRenderQueue() const {
		for (size_t i = 0; i < m_renderableObjects.size(); ++i) {
			m_renderableObjects[i].AddToRenderQueue();
		}
	}
	
	void CompositeRenderable::Render() const {
		return;
	}

	void CompositeRenderable::RenderWire() const {
		for (size_t i = 0; i < m_renderableObjects.size(); ++i) {
			m_renderableObjects[i].RenderWire();
		}
	}
}