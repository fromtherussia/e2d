#ifndef R2D_D3D_GRAPHIC_OBJECT_H
#define R2D_D3D_GRAPHIC_OBJECT_H

#include "IDynamicGeometeryObject.h"

namespace r2d {
	class D3DDynamicGeometeryObject: public IDynamicGeometeryObject {
	public:
		D3DDynamicGeometeryObject(IMaterialPtr pMaterial, D3DRenderContext& context, const Polygon2d& geometry, const Rect& uv, int z);
		D3DDynamicGeometeryObject(IMaterialPtr pMaterial, D3DRenderContext& context, const Polygon2d& geometry, const vec2& tileMetrics, int z);
		virtual ~D3DDynamicGeometeryObject();
		
		// IRenderable Interface
		// Transformations
		virtual void ApplyTransformations(IRenderContext& context) const;
		virtual void IdentityTransformation(IRenderContext& context) const;
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
		virtual void Render(IRenderContext& context) const;
		virtual void RenderWire(IRenderContext& context) const;

		// IDynamicGeometeryObject Interface
		// Geometry data access
		virtual Polygon2d& GetGeometry();
		virtual Rect& GetUv();
		virtual int& GetDepth();
		virtual void SynchronizeWithGpu(IRenderContext& context);
		
	private:
		size_t AllocateBuffer(D3DRenderContext& context, size_t elems);
		void ReleaseBuffer();
		void SetPolygon(D3DRenderContext& context, const Polygon2d& geometry, const Rect& uv, int z, const Rect& boundingRect);
		size_t GetElemsInBufferCount() const;

		// Data
		LPDIRECT3DVERTEXBUFFER9 m_vertexBuffer;
		size_t m_elemsInBuffer;
		D3DXMATRIXA16 m_transform;
		
		// Copy of data in RAM
		Polygon2d m_polygon;
		Rect m_uv;
		int m_z;
		vec2 m_position;
		float m_angle;
	};
	DEFPTR(D3DDynamicGeometeryObject);
};

#endif