#include <cgl/ITimer.h>
#include <cgl/FrameCounter.h>

#include "r2d/ITexture.h"
#include "r2d/IMaterial.h"
#include "r2d/IRenderContext.h"

#include "r2d/D3D/D3DCommon.h"
#include "r2d/D3D/D3DGeometryDefinitions.h"
#include "r2d/D3D/D3DRenderContext.h"
#include "r2d/D3D/D3DTexture.h"
#include "r2d/D3D/D3DEffect.h"
#include "r2d/D3D/D3DMaterial.h"
#include "r2d/D3D/D3DDynamicGeometeryObject.h"

namespace r2d {
	D3DDynamicGeometeryObject::D3DDynamicGeometeryObject(D3DRenderContext& renderContext, IMaterial& material, const Polygon2d& geometry, const Rect& uv, int z, const AnimationProperties& animationProperties):
		IDynamicGeometeryObject(material),
		m_renderContext(renderContext),
		m_vertexBuffer(NULL),
		m_isAnimated(animationProperties.m_useAnimation),
		m_animationProperties(animationProperties),
		m_frameCounter(animationProperties.GetCycleTime(), 0, animationProperties.m_framesCount, true) {
		ResetTransformations();
		//Rect uvFixed(uv.x1, 1.0f - uv.y2, uv.x2, 1.0f - uv.y1);
		SetPolygon(geometry, uv, z, geometry.GetBoundingRect());
		if (m_isAnimated) {
			m_frameCounter.Start();
		}
	}

	/*
	D3DDynamicGeometeryObject::D3DDynamicGeometeryObject(IMaterialPtr pMaterial, const D3DRenderContext& renderContext, const Polygon2d& geometry, const vec2& tileMetrics, int z):
		IDynamicGeometeryObject(pMaterial),
		m_vertexBuffer(NULL) {
		assert(tileMetrics.x > 0.0f);
		assert(tileMetrics.y > 0.0f);
		
		ResetTransformations();
		Rect boundingRect = geometry.GetBoundingRect();
		SetPolygon(renderContext, geometry, Rect(0.0f, 0.0f, boundingRect.Width() / tileMetrics.x, boundingRect.Height() / tileMetrics.y), z, geometry.GetBoundingRect());
	}*/

	D3DDynamicGeometeryObject::~D3DDynamicGeometeryObject() {
		ReleaseBuffer();
	}

	// Transformations
	
	void D3DDynamicGeometeryObject::ApplyTransformations() const {
		LPDIRECT3DDEVICE9 d3dDevice = m_renderContext.GetDevice();

		d3dDevice->SetTransform(D3DTS_WORLD, &m_transform);
	}

	void D3DDynamicGeometeryObject::IdentityTransformation() const {
		LPDIRECT3DDEVICE9 d3dDevice = m_renderContext.GetDevice();
		
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

	void D3DDynamicGeometeryObject::SynchronizeWithGpu() {
		SetPolygon(m_polygon, m_uv, m_z, m_polygon.GetBoundingRect());
	}

	// Rendering

	void D3DDynamicGeometeryObject::Render() const {
		if (m_isAnimated && m_frameCounter.IsActive()) {
			const_cast<FrameCounter&>(m_frameCounter).Update();
			GetMaterial()->SetFloatParam("uOffset", m_frameCounter.GetCount() * m_animationProperties.m_step);
		}

		LPDIRECT3DDEVICE9 d3dDevice = m_renderContext.GetDevice();

		d3dDevice->SetTransform(D3DTS_WORLD, &m_transform);
		d3dDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(StaticGeometryVertex));
		d3dDevice->SetFVF(D3DFVF_STATIC_GEOMETRY_VERTEX);
		d3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, GetElemsInBufferCount() - 2);
	}

	void D3DDynamicGeometeryObject::RenderWire() const {
		m_renderContext.RenderWirePolygon(m_polygon);
	}

	void D3DDynamicGeometeryObject::AddToRenderQueue() const {
		m_renderContext.AddToRenderingQueue(this);
	}

	// Private

	size_t D3DDynamicGeometeryObject::AllocateBuffer(size_t elems) {
		ReleaseBuffer();
		LPDIRECT3DDEVICE9 d3dDevice = m_renderContext.GetDevice();
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

	void D3DDynamicGeometeryObject::SetPolygon(const Polygon2d& geometry, const Rect& uv, int z, const Rect& boundingRect) {
		size_t requiredMemory = AllocateBuffer(geometry.VerteciesCount());

		CGL_CHECK(boundingRect.Width() != 0.0f && boundingRect.Height() != 0.0f);
		// CGL_CHECK(geometry.GetCenter() == vec2()); // FIXME

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
			vertices[i].v = 1.0f - (uv.y1 + (geometry[i].y - boundingRect.y1) / boundingRect.Height() * vRange);
		}
		m_vertexBuffer->Unlock();
		m_polygon = geometry;
		m_uv = uv;
		m_z = z;
	}

	size_t D3DDynamicGeometeryObject::GetElemsInBufferCount() const {
		return m_elemsInBuffer;
	}

	void D3DDynamicGeometeryObject::StartAnimation() {
		m_frameCounter.Start();
	}

	void D3DDynamicGeometeryObject::StopAnimation() {
		m_frameCounter.Stop();
	}

	void D3DDynamicGeometeryObject::PauseAnimation() {
		m_frameCounter.Pause();
	}

	void D3DDynamicGeometeryObject::UnpauseAnimation() {
		m_frameCounter.Unpause();
	}

	bool D3DDynamicGeometeryObject::IsAnimationRunning() const {
		return m_frameCounter.IsActive();
	}
}