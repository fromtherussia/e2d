#ifndef R2D_COMPOSITE_RENDERABLE_H
#define R2D_COMPOSITE_RENDERABLE_H

#include "r2d/IRenderable.h"

namespace r2d {
	class CompositeRenderable: public IRenderable {
	public:
		CompositeRenderable(IRenderContext& renderContext, IMaterial* materialPtr);
		virtual ~CompositeRenderable();
		// Adding renderable objects
		CompositeRenderable& AddRenderable(std::auto_ptr<IRenderable> renderablePtr, vec2 offset);
		IRenderable& operator [] (uint index);
		void RemoveRenderables();
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
		virtual void AddToRenderQueue() const;
		virtual void Render() const;
		virtual void RenderWire() const;

		// Transformations
		virtual void ApplyTransformations() const {};
		virtual void IdentityTransformation() const {};
		
		// Sorting
		virtual bool HasAlpha() const { return false; };
		virtual int GetZ() const { return 0.0f; };
		virtual int GetMaterialId() const { return 0; };
		
	
	private:
		typedef boost::ptr_vector<IRenderable> RenderableObjects;
		typedef std::vector<vec2> RenderableObjectsOffsets;
		RenderableObjects m_renderableObjects;
		RenderableObjectsOffsets m_renderableObjectsOffsets;
		IRenderContext& m_renderContext;
		float m_angle;
		vec2 m_position;
	};
}

#endif