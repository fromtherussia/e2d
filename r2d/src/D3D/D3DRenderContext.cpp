#include "r2d/ICamera.h"
#include "r2d/ITexture.h"
#include "r2d/IEffect.h"
#include "r2d/IMaterial.h"
#include "r2d/IRenderable.h"
#include "r2d/IFactory.h"

#include "r2d/D3D/D3DCommon.h"
#include "r2d/D3D/D3DGeometryDefinitions.h"
#include "r2d/D3D/D3DUtils.h"
#include "r2d/D3D/D3DRenderContext.h"
#include "r2d/D3D/D3DCamera.h"
#include "r2d/D3D/D3DTexture.h"
#include "r2d/D3D/D3DEffect.h"
#include "r2d/D3D/D3DMaterial.h"
#include "r2d/D3D/D3DFactory.h"

namespace r2d {
	D3DRenderContext::D3DRenderContext(HWND window):
		m_window(window),
		m_initialized(false),
		m_sceneRenderBegan(false),
		m_done(false) {
	}

	D3DRenderContext::~D3DRenderContext() {
	}

	void D3DRenderContext::ApplyCamera(const D3DCamera& camera) {
		m_d3dDevice->SetTransform(D3DTS_VIEW, &camera.GetViewMatrix());
		m_d3dDevice->SetTransform(D3DTS_PROJECTION, &camera.GetProjectionMatrix());
	}

	LPDIRECT3DDEVICE9 D3DRenderContext::GetDevice() const {
		return m_d3dDevice;
	}

	void D3DRenderContext::SetWorldTransform(const D3DXMATRIXA16& transform) const {
		m_d3dDevice->SetTransform(D3DTS_WORLD, &transform);
	}

	// Init routines
	
	bool D3DRenderContext::Init() {
		if (m_initialized || m_window == NULL) {
			return false;
		}

		if (!InitD3D()) {
			return false;
		}
		
		m_initialized = true;
		return true;
	}

	bool D3DRenderContext::Deinit() {
		if (!m_initialized) {
			return false;
		}
		
		DeinitD3D();
		m_initialized = false;
		return true;
	}


	// Scene routines
	
	void D3DRenderContext::BeginScene() {
		CGL_CHECK(!m_sceneRenderBegan);

		m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		m_d3dDevice->BeginScene();

		m_sceneRenderBegan = true;
	}

	void D3DRenderContext::EndScene() {
		CGL_CHECK(m_sceneRenderBegan);

		m_sceneRenderBegan = false;

		m_d3dDevice->EndScene();
		m_d3dDevice->Present(NULL, NULL, NULL, NULL);
	}

	void D3DRenderContext::ApplyCamera(const ICamera& camera) {
		ApplyCamera(dynamic_cast<const D3DCamera&>(camera));
	}

	// World transform (for onfly render)

	void D3DRenderContext::SetWorldTransform(const vec2& position, float angle) const {
		D3DXMATRIXA16 transform = ToMatrixD3D(position, angle);
		SetWorldTransform(transform);
	}

	void D3DRenderContext::ResetWorldTransform() const {
		D3DXMATRIXA16 identity;
		D3DXMatrixIdentity(&identity);
		SetWorldTransform(identity);
	}

	// On fly render routines

	void D3DRenderContext::RenderPoint(const vec2& point, const ivec3& color, float pointSize) const {
		WireGeometryPoint points[1];
		points[0].x = point.x;
		points[0].y = point.y;
		points[0].z = MAX_ZCHOOORD;
		points[0].size = pointSize;
		points[0].color = D3DCOLOR_XRGB(color.x, color.y, color.z);

		m_d3dDevice->SetFVF(D3DFVF_WIRE_GEOMETRY_POINT);
		m_d3dDevice->DrawPrimitiveUP(D3DPT_POINTLIST, 1, static_cast<void*>(points), sizeof(WireGeometryPoint));
	}

	void D3DRenderContext::RenderLine(const vec2& point1, const vec2& point2, const ivec3& color) const {
		WireGeometryVertex points[3];
		points[0].x = point1.x;
		points[0].y = point1.y;
		points[0].z = MAX_ZCHOOORD;
		//points[0].rhw = 1.0f;
		points[0].color = D3DCOLOR_XRGB(color.x, color.y, color.z);

		points[1].x = point2.x;
		points[1].y = point2.y;
		points[1].z = MAX_ZCHOOORD;
		//points[1].rhw = 1.0f;
		points[1].color = D3DCOLOR_XRGB(color.x, color.y, color.z);

		m_d3dDevice->SetFVF(D3DFVF_WIRE_GEOMETRY_VERTEX);
		m_d3dDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, static_cast<void*>(points), sizeof(WireGeometryVertex));
	}

	void D3DRenderContext::RenderWireRectangle(const Rect& geometry, const ivec3& color) const {
		RenderLine(geometry.LeftBottomCorner(), geometry.RightBottomCorner(), color);
		RenderLine(geometry.RightBottomCorner(), geometry.RightTopCorner(), color);
		RenderLine(geometry.RightTopCorner(), geometry.LeftTopCorner(), color);
		RenderLine(geometry.LeftTopCorner(), geometry.LeftBottomCorner(), color);
	}

	void D3DRenderContext::RenderSolidRectangle(const Rect& geometry, const ivec3& color) const {
		RenderLine(geometry.LeftBottomCorner(), geometry.RightBottomCorner(), color);
		RenderLine(geometry.RightBottomCorner(), geometry.RightTopCorner(), color);
		RenderLine(geometry.RightTopCorner(), geometry.LeftTopCorner(), color);
		RenderLine(geometry.LeftTopCorner(), geometry.LeftBottomCorner(), color);
	}

	void D3DRenderContext::RenderWireCircle(const Circle& c, const ivec3& color) const {
		WireGeometryVertex points[CIRCLE_SECTORS_COUNT + 1];
		float pi2 = 2.0f * M_PI;
		float sectorSize = pi2 / CIRCLE_SECTORS_COUNT;

		int pointNo = 0;
		for (float angle = 0.0f; angle < pi2; angle += sectorSize, ++pointNo) {
			points[pointNo].x = c.GetOrigin().x + glm::cos(angle) * c.GetRadius();
			points[pointNo].y = c.GetOrigin().y + glm::sin(angle) * c.GetRadius();
			points[pointNo].z = MAX_ZCHOOORD;
			points[pointNo].color = D3DCOLOR_XRGB(color.x, color.y, color.z);
		}
		points[CIRCLE_SECTORS_COUNT].x = c.GetOrigin().x + c.GetRadius();
		points[CIRCLE_SECTORS_COUNT].y = c.GetOrigin().y;
		points[CIRCLE_SECTORS_COUNT].z = MAX_ZCHOOORD;
		points[CIRCLE_SECTORS_COUNT].color = D3DCOLOR_XRGB(color.x, color.y, color.z);

		m_d3dDevice->SetFVF(D3DFVF_WIRE_GEOMETRY_VERTEX);
		m_d3dDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, CIRCLE_SECTORS_COUNT, static_cast<void*>(points), sizeof(WireGeometryVertex));
	}

	void D3DRenderContext::RenderSolidCircle(const Circle& c, const ivec3& color) const {
		WireGeometryVertex points[CIRCLE_SECTORS_COUNT + 1];
		float pi2 = 2.0f * M_PI;
		float sectorSize = pi2 / CIRCLE_SECTORS_COUNT;

		int pointNo = 0;
		for(float angle = 0.0f; angle < pi2; angle += sectorSize, ++pointNo) {
			points[pointNo].x = c.GetOrigin().x + glm::cos(angle) * c.GetRadius();
			points[pointNo].y = c.GetOrigin().y + glm::sin(angle) * c.GetRadius();
			points[pointNo].z = MAX_ZCHOOORD;
			points[pointNo].color = D3DCOLOR_XRGB(color.x, color.y, color.z);
		}
		points[CIRCLE_SECTORS_COUNT].x = c.GetOrigin().x + c.GetRadius();
		points[CIRCLE_SECTORS_COUNT].y = c.GetOrigin().y;
		points[CIRCLE_SECTORS_COUNT].z = MAX_ZCHOOORD;
		points[CIRCLE_SECTORS_COUNT].color = D3DCOLOR_XRGB(color.x, color.y, color.z);

		m_d3dDevice->SetFVF(D3DFVF_WIRE_GEOMETRY_VERTEX);
		m_d3dDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, CIRCLE_SECTORS_COUNT, static_cast<void*>(points), sizeof(WireGeometryVertex));
	}

	void D3DRenderContext::RenderWirePolygon(const Polygon2d& p, const ivec3& color) const {
		WireGeometryVertex* points = new WireGeometryVertex[p.VerteciesCount() + 1];
		for (uint i = 0; i <= p.VerteciesCount(); ++i) {
			if (i == p.VerteciesCount()) {
				points[i].x = p[0].x;
				points[i].y = p[0].y;
				points[i].z = MAX_ZCHOOORD;
				points[i].color = D3DCOLOR_XRGB(color.x, color.y, color.z);
			} else {
				points[i].x = p[i].x;
				points[i].y = p[i].y;
				points[i].z = MAX_ZCHOOORD;
				points[i].color = D3DCOLOR_XRGB(color.x, color.y, color.z);
			}
		}

		m_d3dDevice->SetFVF(D3DFVF_WIRE_GEOMETRY_VERTEX);
		m_d3dDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, p.VerteciesCount(), static_cast<void*>(points), sizeof(WireGeometryVertex));

		delete[] points;
	}

	void D3DRenderContext::RenderSolidPolygon(const Polygon2d& p, const ivec3& color) const {
		WireGeometryVertex* points = new WireGeometryVertex[p.VerteciesCount() + 1];
		for (uint i = 0; i <= p.VerteciesCount(); ++i) {
			if (i == p.VerteciesCount()) {
				points[i].x = p[0].x;
				points[i].y = p[0].y;
				points[i].z = MAX_ZCHOOORD;
				points[i].color = D3DCOLOR_XRGB(color.x, color.y, color.z);
			} else {
				points[i].x = p[i].x;
				points[i].y = p[i].y;
				points[i].z = MAX_ZCHOOORD;
				points[i].color = D3DCOLOR_XRGB(color.x, color.y, color.z);
			}
		}

		m_d3dDevice->SetFVF(D3DFVF_WIRE_GEOMETRY_VERTEX);
		m_d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, p.VerteciesCount(), static_cast<void*>(points), sizeof(WireGeometryVertex));

		delete[] points;
	}

	void D3DRenderContext::RenderWorldAxises() const {
		RenderLine(vec2(0.0f, 0.0f), vec2(AXIS_LENGTH, 0.0f), ivec3(0xFF, 0, 0));
		RenderLine(vec2(0.0f, 0.0f), vec2(0.0f, AXIS_LENGTH), ivec3(0, 0, 0xFF));
	}

	// Preloaded primitives render routines

	void D3DRenderContext::AddToRenderingQueue(const IRenderable* renderableObjectPtr) {
		IMaterial* materialPtr = renderableObjectPtr->GetMaterial();
		if (renderableObjectPtr->HasAlpha()) {
			m_alphaObjectsQueue[renderableObjectPtr->GetZ()][materialPtr->GetMaterialId()].push_back(renderableObjectPtr);
		} else {
			m_solidObjectsQueue[materialPtr->GetMaterialId()].push_back(renderableObjectPtr);
		}
		m_materials[materialPtr->GetMaterialId()] = materialPtr;
	}
	
	void D3DRenderContext::RenderQueuedObjects(bool isDebug) {
		for (ObjectsQueue::iterator i = m_solidObjectsQueue.begin(); i != m_solidObjectsQueue.end(); ++i) {
			Render((D3DMaterial*)m_materials[i->first], i->second);
		}
		for (AlphaObjectsQueue::iterator i = m_alphaObjectsQueue.begin(); i != m_alphaObjectsQueue.end(); ++i) {
			for (ObjectsQueue::iterator j = i->second.begin(); j != i->second.end(); ++j) {
				Render((D3DMaterial*)m_materials[j->first], j->second);
			}
		}
		m_solidObjectsQueue.clear();
		m_alphaObjectsQueue.clear();
		m_materials.clear();
	}

	// Factory

	std::auto_ptr<IFactory> D3DRenderContext::GetFactory() {
		return std::auto_ptr<IFactory>(new D3DFactory(*this));
	}
	
	bool D3DRenderContext::InitD3D() {
		D3DPRESENT_PARAMETERS d3dpp;

		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = m_window;

		m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
		m_d3d->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			m_window,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_d3dDevice
		);
		m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		m_d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		return true;
	}

	bool D3DRenderContext::DeinitD3D() {
		m_d3dDevice->Release();
		m_d3d->Release();

		return true;
	}

	void D3DRenderContext::Render(D3DMaterial* material, RenderQueue& renderableObjects) {
		for (RenderQueue::const_iterator i = renderableObjects.begin(); i != renderableObjects.end(); ++i) {
			uint passesCount = material->BeginPasses("RenderScene");
			for (uint passNo = 0; passNo < passesCount; ++passNo) {
				(*i)->ApplyTransformations();
				material->SetMatrices();
				material->BeginPass(passNo);
				(*i)->Render();
				(*i)->IdentityTransformation();
				material->EndPass();
			}
			material->EndPasses();
		}
	}
}