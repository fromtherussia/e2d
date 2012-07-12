#ifndef P2D_DEBUG_RENDERER_H
#define P2D_DEBUG_RENDERER_H

#include "p2d/Common.h"

namespace p2d {
	#define DEFAULT_COLOR_RGB ivec3(0xFF, 0xFF, 0xFF)
	#define JOINT_COLOR_RGB ivec3(0xFF, 0xFF, 0)
	#define SHAPE_COLOR_RGB ivec3(0, 0xFF, 0)

	class DebugRenderer {
	public:
		DebugRenderer() {};
		virtual ~DebugRenderer() {};
		virtual void SetWorldTransform(const vec2& position, float angle) const = 0;
		virtual void ResetWorldTransform() const = 0;
		virtual void RenderPoint(const vec2& point, const ivec3& color = DEFAULT_COLOR_RGB, float pointSize = 1.0f) const = 0;
		virtual void RenderLine(const vec2& point1, const vec2& point2, const ivec3& color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderPolygonalChain(const PolygonalChain2d& p, const ivec3& color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderWireRectangle(const Rect& geometry, const ivec3& color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderSolidRectangle(const Rect& geometry, const ivec3& color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderWireCircle(const Circle& c, const ivec3& color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderSolidCircle(const Circle& c, const ivec3& color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderWirePolygon(const Polygon2d& p, const ivec3& color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderSolidPolygon(const Polygon2d& p, const ivec3& color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderWorldAxises() const = 0;
	};
}

#endif