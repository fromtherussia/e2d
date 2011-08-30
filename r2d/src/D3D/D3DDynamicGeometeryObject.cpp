#include <assert.h>

#include "ITexture.h"
#include "IMaterial.h"
#include "IRenderContext.h"

#include "D3DCommon.h"
#include "D3DGeometryDefinitions.h"
#include "D3DRenderContext.h"
#include "D3DTexture.h"
#include "D3DEffect.h"
#include "D3DMaterial.h"
#include "D3DDynamicGeometeryObject.h"

namespace r2d {
	// Public

	D3DDynamicGeometeryObject::D3DDynamicGeometeryObject(IMaterialPtr pMaterial, D3DRenderContext& context, const Polygon2d& geometry, const Rect& uv, int z):
		IDynamicGeometeryObject(pMaterial),
		m_vertexBuffer(NULL) {
		ResetTransformations();
		SetPolygon(context, geometry, uv, z, geometry.GetBoundingRect());
	}

	D3DDynamicGeometeryObject::D3DDynamicGeometeryObject(IMaterialPtr pMaterial, D3DRenderContext& context, const Polygon2d& geometry, const vec2& tileMetrics, int z):
		IDynamicGeometeryObject(pMaterial),
		m_vertexBuffer(NULL) {
		assert(tileMetrics.x > 0.0f);
		assert(tileMetrics.y > 0.0f);
		
		ResetTransformations();
		Rect boundingRect = geometry.GetBoundingRect();
		SetPolygon(context, geometry, Rect(0.0f, 0.0f, boundingRect.Width() / tileMetrics.x, boundingRect.Height() / tileMetrics.y), z, geometry.GetBoundingRect());
	}

	D3DDynamicGeometeryObject::~D3DDynamicGeometeryObject() {
		ReleaseBuffer();
	}

	// Transformations
	
	void D3DDynamicGeometeryObject::ApplyTransformations(IRenderContext& context) const {
		D3DRenderContext& d3dContext = (D3DRenderContext&)context;
		LPDIRECT3DDEVICE9& d3dDevice = d3dContext.GetDevice();

		d3dDevice->SetTransform(D3DTS_WORLD, &m_transform);
	}

	void D3DDynamicGeometeryObject::IdentityTransformation(IRenderContext& context) const {
		D3DRenderContext& d3dContext = (D3DRenderContext&)context;
		LPDIRECT3DDEVICE9& d3dDevice = d3dContext.GetDevice();
		
		D3DXMATRIXA16 transformaton;
		D3DXMatrixIdentity(&transformaton);
		d3dDevice->SetTransform(D3DTS_WORLD, &transformaton);
	}

	void D3DDynamicGeometeryObject::SetTransformations(const vec2& position, float angle) {
		if (m_isRotationOriginSet) {
			D3DXMATRIXA16 rotationOriginTranslation;
			D3DXMATRIXA16 originTranslation;
			D3DXMATRIXA16 rotation;
			
			D3DXMatrixTranslation(&rotationOriginTranslation, m_rotationOrigin.x, m_rotationOrigin.y, 0.0f);
			D3DXMatrixTranslation(&originTranslation, position.x - m_rotationOrigin.x, position.y - m_rotationOrigin.y, 0.0f);
			D3DXMatrixRotationZ(&rotation, angle);

			D3DXMatrixMultiply(&m_transform, &originTranslation, &rotation);
			D3DXMatrixMultiply(&m_transform, &m_transform, &rotationOriginTranslation);
		} else {
			D3DXMATRIXA16 newTranslation;
			D3DXMATRIXA16 newRotation;
			
			D3DXMatrixTranslation(&newTranslation, position.x, position.y, 0.0f);
			D3DXMatrixRotationZ(&newRotation, angle);

			D3DXMatrixMultiply(&m_transform, &newRotation, &newTranslation);
		}

		m_position = position;
		m_angle = angle;
	}

	void D3DDynamicGeometeryObject::SetPosition(const vec2& position) {
		SetTransformations(position, m_angle);
	}

	vec2 D3DDynamicGeometeryObject::GetPosition() const {
		return m_position;
	}

	void D3DDynamicGeometeryObject::SetRotation(float angle) {
		SetTransformations(m_position, angle);
	}

	float D3DDynamicGeometeryObject::GetRotation() const {
		return m_angle;
	}

	void D3DDynamicGeometeryObject::ResetTransformations() {
		D3DXMatrixIdentity(&m_transform);

		m_angle = 0.0f;
		m_position = vec2(0.0f, 0.0f);
	}

	// Invisible objects optimization

	Rect D3DDynamicGeometeryObject::GetBoundingRect() const {
		return m_polygon.GetBoundingRect() + m_position;
	}

	// Sorting

	bool D3DDynamicGeometeryObject::HasAlpha() const {
		return false;
	}

	int D3DDynamicGeometeryObject::GetZ() const {
		return m_z;
	}

	int D3DDynamicGeometeryObject::GetMaterialId() const {
		return 0;
	}

	// Geometry data access

	Polygon2d& D3DDynamicGeometeryObject::GetGeometry() {
		return m_polygon;
	}

	Rect& D3DDynamicGeometeryObject::GetUv() {
		return m_uv;
	}

	int& D3DDynamicGeometeryObject::GetDepth() {
		return m_z;
	}

	void D3DDynamicGeometeryObject::SynchronizeWithGpu(IRenderContext& context) {
		SetPolygon((D3DRenderContext&)context, m_polygon, m_uv, m_z, m_polygon.GetBoundingRect());
	}

	// Rendering

	void D3DDynamicGeometeryObject::Render(IRenderContext& context) const {
		D3DRenderContext& d3dContext = (D3DRenderContext&)context;
		LPDIRECT3DDEVICE9& d3dDevice = d3dContext.GetDevice();

		d3dDevice->SetTransform(D3DTS_WORLD, &m_transform);
		d3dDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(StaticGeometryVertex));
		d3dDevice->SetFVF(D3DFVF_STATIC_GEOMETRY_VERTEX);
		d3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, GetElemsInBufferCount() - 2);
	}

	void D3DDynamicGeometeryObject::RenderWire(IRenderContext& context) const {
		context.RenderWirePolygon(m_polygon);
	}

	// Private

	size_t D3DDynamicGeometeryObject::AllocateBuffer(D3DRenderContext& context, size_t elems) {
		ReleaseBuffer();
		LPDIRECT3DDEVICE9& d3dDevice = context.GetDevice();
		size_t requiredMemory = elems * sizeof(StaticGeometryVertex);
		if (FAILED(d3dDevice->CreateVertexBuffer(requiredMemory, 0, D3DFVF_STATIC_GEOMETRY_VERTEX, D3DPOOL_DEFAULT, &m_vertexBuffer, NULL))) {
			throw std::runtime_error("can't create D3D buffer");
		}
		if (m_vertexBuffer == NULL) {
			throw std::runtime_error("can't create D3D buffer");
		}
		m_elemsInBuffer = elems;
		return requiredMemory;
	}

	void D3DDynamicGeometeryObject::ReleaseBuffer() {
		if (m_vertexBuffer != NULL) {
			m_vertexBuffer->Release();
		}
	}

	void D3DDynamicGeometeryObject::SetPolygon(D3DRenderContext& context, const Polygon2d& geometry, const Rect& uv, int z, const Rect& boundingRect) {
		size_t requiredMemory = AllocateBuffer(context, geometry.VerteciesCount());

		assert(boundingRect.Width() != 0.0f && boundingRect.Height() != 0.0f);
		assert(geometry.GetCenter() == vec2());

		float uRange = uv.Width();
		float vRange = uv.Height();

		StaticGeometryVertex* vertices;
		m_vertexBuffer->Lock(0, requiredMemory, (void**)(&vertices), 0);
		for (uint i = 0; i < geometry.VerteciesCount(); ++i) {
			vertices[i].x = geometry[i].x;
			vertices[i].y = geometry[i].y;
			vertices[i].z = z;
			vertices[i].color = 0xFFFFFFFF;
			vertices[i].u = uv.x1 + (geometry[i].x - boundingRect.x1) / boundingRect.Width() * uRange;
			vertices[i].v = uv.y1 + (geometry[i].y - boundingRect.y1) / boundingRect.Height() * vRange;
		}
		m_vertexBuffer->Unlock();
		m_polygon = geometry;
		m_uv = uv;
		m_z = z;
	}

	size_t D3DDynamicGeometeryObject::GetElemsInBufferCount() const {
		return m_elemsInBuffer;
	}
}