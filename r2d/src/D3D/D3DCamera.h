#ifndef R2D_D3D_CAMERA_H
#define R2D_D3D_CAMERA_H

#include "ICamera.h"

namespace r2d {
	class D3DCamera: public ICamera {
	public:
		D3DCamera(const Rect& visibleRect, float zNear = 0.0f, float zFar = 1.0f);
		~D3DCamera();
		
		virtual bool SetVisibleRect(const Rect& visibleRect, float zNear, float zFar);
		virtual Rect GetVisibleRect() const;
		virtual void Move(const vec2& direction);
		virtual void SetPosition(const vec2& position);
		virtual vec2 GetPosition() const;

	private:
		D3DXMATRIXA16 GetViewMatrix() const;
		D3DXMATRIXA16 GetProjectionMatrix() const;
		D3DXMATRIXA16 GetViewProjection() const;

		Rect m_visibleRect;
		vec2 m_position;
		D3DXMATRIXA16 m_viewMatrix;
		D3DXMATRIXA16 m_projectionMatrix;

		friend class D3DRenderContext;
	};
	DEFPTR(D3DCamera);
}

#endif