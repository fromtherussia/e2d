#ifndef R2D_IRENDER_CONTEXT_H
#define R2D_IRENDER_CONTEXT_H

#include "r2d/Common.h"

namespace r2d {
	#define DEFAULT_COLOR_RGB ivec3(0xFF, 0xFF, 0xFF)

	class IRenderContext {
	public:
		IRenderContext() {};
		virtual ~IRenderContext() {};
		// Init routines
		virtual bool Init() = 0;
		virtual bool Deinit() = 0;
		// Scene routines
		virtual void BeginScene() = 0;
		virtual void EndScene() = 0;
		virtual void ApplyCamera(const ICamera& camera) = 0;
		// World transform (for onfly render)
		virtual void SetWorldTransform(const vec2& position, float angle) const = 0;
		virtual void ResetWorldTransform() const = 0;
		// On fly render routines
		virtual void RenderPoint(const vec2& point, const ivec3& color = DEFAULT_COLOR_RGB, float pointSize = 1.0f) const = 0;
		virtual void RenderLine(const vec2& point1, const vec2& point2, const ivec3& color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderWireRectangle(const Rect& geometry, const ivec3& color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderSolidRectangle(const Rect& geometry, const ivec3& color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderWireCircle(const Circle& c, const ivec3& color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderSolidCircle(const Circle& c, const ivec3& color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderWirePolygon(const Polygon2d& p, const ivec3& color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderSolidPolygon(const Polygon2d& p, const ivec3& color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderWorldAxises() const = 0;
		/*
			Очередь хранит указатели на объекты IRenderable до вызова RenderQueuedObjects.
			Во время вызова RenderQueuedObjects объекты сортируются по альфа каналу и материалу,
			затем выводятся на экран.
		*/
		// Custom primitives render routines
		virtual void AddToRenderingQueue(const IRenderable* renderableObjectPtr) = 0;
		virtual void RenderQueuedObjects(bool isDebug) = 0;

		// Factory
		virtual std::auto_ptr<IFactory> GetFactory() = 0;		
	};
}

#endif