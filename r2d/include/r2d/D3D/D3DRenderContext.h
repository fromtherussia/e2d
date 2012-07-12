#ifndef R2D_D3D_RENDER_CONTEXT_H
#define R2D_D3D_RENDER_CONTEXT_H

#include "r2d/IRenderContext.h"

namespace r2d {
	#define CIRCLE_SECTORS_COUNT 16

	class D3DCamera;
	class D3DMaterial;

	class D3DRenderContext: public IRenderContext {
	public:
		D3DRenderContext(HWND window);
		virtual ~D3DRenderContext();

		void ApplyCamera(const D3DCamera& camera);
		LPDIRECT3DDEVICE9 GetDevice() const;
		void SetWorldTransform(const D3DXMATRIXA16& transform) const;

		// Init routines
		virtual bool Init();
		virtual bool Deinit();

		// Scene routines
		virtual void BeginScene();
		virtual void EndScene();
		virtual void ApplyCamera(const ICamera& camera);

		// World transform (for onfly render)
		virtual void SetWorldTransform(const vec2& position, float angle) const;
		virtual void ResetWorldTransform() const;

		// On fly render routines
		virtual void RenderPoint(const vec2& point, const ivec3& color = DEFAULT_COLOR_RGB, float pointSize = 1.0f) const;
		virtual void RenderLine(const vec2& point1, const vec2& point2, const ivec3& color = DEFAULT_COLOR_RGB) const;
		virtual void RenderPolygonalChain(const PolygonalChain2d& p, const ivec3& color = DEFAULT_COLOR_RGB) const;
		virtual void RenderWireRectangle(const Rect& geometry, const ivec3& color = DEFAULT_COLOR_RGB) const;
		virtual void RenderSolidRectangle(const Rect& geometry, const ivec3& color = DEFAULT_COLOR_RGB) const;
		virtual void RenderWireCircle(const Circle& c, const ivec3& color = DEFAULT_COLOR_RGB) const;
		virtual void RenderSolidCircle(const Circle& c, const ivec3& color = DEFAULT_COLOR_RGB) const;
		virtual void RenderWirePolygon(const Polygon2d& p, const ivec3& color = DEFAULT_COLOR_RGB) const;
		virtual void RenderSolidPolygon(const Polygon2d& p, const ivec3& color = DEFAULT_COLOR_RGB) const;
		virtual void RenderWorldAxises() const;

		// Custom primitives render routines
		virtual void AddToRenderingQueue(const IRenderable* renderableObjectPtr);
		virtual void RenderQueuedObjects(bool isDebug);

		// Factory
		virtual std::auto_ptr<IFactory> GetFactory();

	private:
		// Rendering queues.
		typedef std::vector<const IRenderable*> RenderQueue;
		typedef std::map<uint, const IMaterial*> MaterialsQueue;
		typedef std::map<uint, RenderQueue> ObjectsQueue;
		typedef std::map<int, ObjectsQueue> AlphaObjectsQueue;

		MaterialsQueue m_materials;
		ObjectsQueue m_solidObjectsQueue; // Sorted by material
		AlphaObjectsQueue m_alphaObjectsQueue; // Sorted by z, then by material

		HWND m_window;
		LPDIRECT3D9 m_d3d;
		LPDIRECT3DDEVICE9 m_d3dDevice;
		bool m_initialized;
		bool m_done;
		bool m_sceneRenderBegan;

		bool InitD3D();
		bool DeinitD3D();
		void Render(D3DMaterial* material, RenderQueue& renderableObjects);
	};
}

#endif
