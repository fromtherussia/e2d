#ifndef R2D_IRENDER_CONTEXT_H
#define R2D_IRENDER_CONTEXT_H

#include "Common.h"

namespace r2d {
	#define DEFAULT_COLOR_RGB ivec3(0xFF, 0xFF, 0xFF)

	PREDECL_CLASS_WITH_PTR(ICamera);
	PREDECL_CLASS_WITH_PTR(IRenderable);
	PREDECL_CLASS_WITH_PTR(IMaterial);
	PREDECL_CLASS_WITH_PTR(IFactory);

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
		virtual void RenderPoint(vec2 point, ivec3 color = DEFAULT_COLOR_RGB, float pointSize = 1.0f) const = 0;
		virtual void RenderLine(vec2 point1, vec2 point2, ivec3 color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderWireRectangle(Rect geometry, ivec3 color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderSolidRectangle(Rect geometry, ivec3 color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderWireCircle(const Circle& c, ivec3 color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderSolidCircle(const Circle& c, ivec3 color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderWirePolygon(const Polygon2d& p, ivec3 color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderSolidPolygon(const Polygon2d& p, ivec3 color = DEFAULT_COLOR_RGB) const = 0;
		virtual void RenderWorldAxises(const vec2& position, float angle) const = 0;

		/*
			Очередь хранит указатели на объекты IRenderable до вызова RenderQueuedObjects.
			Во время вызова RenderQueuedObjects объекты сортируются по альфа каналу и материалу,
			затем выводятся на экран.
		*/
		// Custom primitives render routines
		virtual void AddToRenderingQueue(const IRenderable* pRenderableObject) = 0;
		virtual void RenderQueuedObjects(bool isDebug) = 0;

		// Factory
		virtual IFactory* GetFactory() = 0;		
	};
	DEFPTR(IRenderContext);
}

#endif