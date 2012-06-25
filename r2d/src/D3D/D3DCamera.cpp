#include "r2d/D3D/D3DCommon.h"

#include "r2d/D3D/D3DCamera.h"

namespace r2d {
	D3DCamera::D3DCamera(const Rect& visibleRect, float zNear, float zFar) {
		if (!SetVisibleRect(visibleRect, zNear, zFar)) {
			throw std::logic_error("Invalid visible rect");
		}
		
		D3DXMatrixIdentity(&m_viewMatrix);
	}

	D3DCamera::~D3DCamera() {
	}

	bool D3DCamera::SetVisibleRect(const Rect& visibleRect, float zNear, float zFar) {
		if (!visibleRect.Validate()) {
			return false;
		}
		
		D3DXMatrixOrthoOffCenterLH(
			&m_projectionMatrix, 
			visibleRect.x1, 
			visibleRect.x2, 
			visibleRect.y1, 
			visibleRect.y2, 
			zNear, 
			zFar
		);
		
		m_visibleRect = visibleRect;
		SetPosition(m_visibleRect.Center());
		return true;
	}

	Rect D3DCamera::GetVisibleRect() const {
		return m_visibleRect + (m_position - m_visibleRect.Center());
	}

	void D3DCamera::SetPosition(const vec2& position) {
		D3DXMatrixTranslation(&m_viewMatrix, -position.x, -position.y, 0.0f);
		m_position = position;
	}

	vec2 D3DCamera::GetPosition() const {
		return m_position;
	}

	void D3DCamera::Move(const vec2& direction) {
		SetPosition(m_position + direction);
	}

	D3DXMATRIXA16 D3DCamera::GetViewMatrix() const {
		return m_viewMatrix;
	}

	D3DXMATRIXA16 D3DCamera::GetProjectionMatrix() const {
		return m_projectionMatrix;
	}

	D3DXMATRIXA16 D3DCamera::GetViewProjection() const {
		return m_viewMatrix * m_projectionMatrix;
	}
}