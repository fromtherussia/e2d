#ifndef R2D_ICAMERA_H
#define R2D_ICAMERA_H

#include "Common.h"

namespace r2d {
	class ICamera {
	public:
		ICamera() {};
		virtual ~ICamera() {};

		virtual bool SetVisibleRect(const Rect& visibleRect, float zNear, float zFar) = 0;
		virtual Rect GetVisibleRect() const = 0;
		virtual void Move(const vec2& direction) = 0;
		virtual void SetPosition(const vec2& position) = 0;
		virtual vec2 GetPosition() const = 0;
	};
	DEFPTR(ICamera);
}

#endif