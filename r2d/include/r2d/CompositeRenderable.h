#ifndef R2D_COMPOSITE_RENDERABLE_H
#define R2D_COMPOSITE_RENDERABLE_H

#include "Common.h"

namespace r2d {
	class IRenderable;
	class IRenderContext;
	PREDECL_CLASS_WITH_PTR(IRenderable);

	class CompositeRenderable {
	public:
		CompositeRenderable();
		virtual ~CompositeRenderable();
		// Adding renderable objects
		CompositeRenderable& AddRenderable(IRenderable* renderable, vec2 offset);
		IRenderable& operator [](uint index);
		// Transformations
		virtual void SetTransformations(const vec2& position, float angle);
		virtual void SetPosition(const vec2& position);
		virtual vec2 GetPosition() const;
		virtual void SetRotation(float angle);
		virtual float GetRotation() const;
		virtual void ResetTransformations();
		// Invisible objects optimization
		virtual Rect GetBoundingRect() const;
		// Rendering
		virtual void Render(IRenderContext& context) const;
		virtual void RenderWire(IRenderContext& context) const;
	
	private:
		typedef std::vector<IRenderablePtr> RenderableObjects;
		typedef std::vector<vec2> RenderableObjectsOffsets;
		RenderableObjects m_renderableObjects;
		RenderableObjectsOffsets m_renderableObjectsOffsets;
		float m_angle;
		vec2 m_position;
	};
	DEFPTR(CompositeRenderable);
}

#endif