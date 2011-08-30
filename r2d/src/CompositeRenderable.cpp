#include "IRenderable.h"
#include "IRenderContext.h"

#include "CompositeRenderable.h"

namespace r2d {
	CompositeRenderable::CompositeRenderable() {
	}

	CompositeRenderable::~CompositeRenderable() {

	}

	CompositeRenderable& CompositeRenderable::AddRenderable(IRenderable* renderable, vec2 offset) {
		m_renderableObjects.push_back(IRenderablePtr(renderable));
		renderable->SetPosition(offset);
		m_renderableObjectsOffsets.push_back(offset);
		return *this;
	}

	IRenderable& CompositeRenderable::operator [](uint index) {
		if (index >= m_renderableObjects.size()) {
			throw std::logic_error("index is out of range");
		}
		return *m_renderableObjects[index];
	}
	
	void CompositeRenderable::SetTransformations(const vec2& position, float angle) {
		m_position = position;
		m_angle = angle;
		for (size_t i = 0; i < m_renderableObjects.size(); ++i) {
			m_renderableObjects[i]->SetRotationOrigin(m_position);
			m_renderableObjects[i]->SetTransformations(position + m_renderableObjectsOffsets[i], angle);
		}
	}

	void CompositeRenderable::SetPosition(const vec2& position) {
		m_position = position;
		for (size_t i = 0; i < m_renderableObjects.size(); ++i) {
			m_renderableObjects[i]->SetRotationOrigin(m_position);
			m_renderableObjects[i]->SetPosition(position + m_renderableObjectsOffsets[i]);
		}
	}

	vec2 CompositeRenderable::GetPosition() const {
		return m_position;
	}

	void CompositeRenderable::SetRotation(float angle) {
		m_angle = angle;
		for (size_t i = 0; i < m_renderableObjects.size(); ++i) {
			m_renderableObjects[i]->SetRotationOrigin(m_position);
			m_renderableObjects[i]->SetRotation(angle);
		}
	}

	float CompositeRenderable::GetRotation() const {
		return m_angle;
	}

	void CompositeRenderable::ResetTransformations() {
		m_angle = 0.0f;
		m_position = vec2();
		for (size_t i = 0; i < m_renderableObjects.size(); ++i) {
			m_renderableObjects[i]->ResetTransformations();
		}
	}
	
	Rect CompositeRenderable::GetBoundingRect() const {
		return Rect();
	}
	
	void CompositeRenderable::Render(IRenderContext& context) const {
		for (size_t i = 0; i < m_renderableObjects.size(); ++i) {
			context.AddToRenderingQueue(m_renderableObjects[i].get());
		}
	}

	void CompositeRenderable::RenderWire(IRenderContext& context) const {
		for (size_t i = 0; i < m_renderableObjects.size(); ++i) {
			m_renderableObjects[i]->RenderWire(context);
		}
	}
}