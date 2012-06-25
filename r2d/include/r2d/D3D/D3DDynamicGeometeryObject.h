#ifndef R2D_D3D_GRAPHIC_OBJECT_H
#define R2D_D3D_GRAPHIC_OBJECT_H

#include "r2d/IDynamicGeometeryObject.h"

class FrameCounter;

namespace r2d {
	class D3DDynamicGeometeryObject: public IDynamicGeometeryObject {
	public:
		D3DDynamicGeometeryObject(
			D3DRenderContext& renderContext,
			IMaterial* materialPtr,
			const Polygon2d& geometry,
			const Rect& uv,
			int z,
			const AnimationProperties& animationProperties = AnimationProperties()
		);
		virtual ~D3DDynamicGeometeryObject();
		
		// IRenderable Interface
		// Transformations
		virtual void ApplyTransformations() const;
		virtual void IdentityTransformation() const;
		virtual void SetTransformations(const vec2& position, float angle);
		virtual void SetPosition(const vec2& position);
		virtual vec2 GetPosition() const;
		virtual void SetRotation(float angle);
		virtual float GetRotation() const;
		virtual void ResetTransformations();
		// Invisible objects optimization
		virtual Rect GetBoundingRect() const;
		// Sorting
		virtual bool HasAlpha() const;
		virtual int GetZ() const;
		virtual int GetMaterialId() const;
		// Rendering
		virtual void Render() const;
		virtual void RenderWire() const;
		virtual void AddToRenderQueue() const;
		
		// IDynamicGeometeryObject Interface
		// Geometry data access
		virtual Polygon2d& GetGeometry();
		virtual Rect& GetUv();
		virtual int& GetDepth();
		virtual void SynchronizeWithGpu();
		
		// Animation
		virtual void StartAnimation();
		virtual void StopAnimation();
		virtual void PauseAnimation();
		virtual void UnpauseAnimation();
		virtual bool IsAnimationRunning() const;
		
	private:
		size_t AllocateBuffer(size_t elems);
		void ReleaseBuffer();
		void SetPolygon(const Polygon2d& geometry, const Rect& uv, int z, const Rect& boundingRect);
		size_t GetElemsInBufferCount() const;

		// Data
		LPDIRECT3DVERTEXBUFFER9 m_vertexBuffer;
		size_t m_elemsInBuffer;
		D3DXMATRIXA16 m_transform;
		D3DRenderContext& m_renderContext;
		
		// Copy of data in RAM
		Polygon2d m_polygon;
		Rect m_uv;
		int m_z;
		vec2 m_position;
		float m_angle;

		// Animation data
		bool m_isAnimated;
		FrameCounter m_frameCounter;
		AnimationProperties m_animationProperties;
	};
};

#endif