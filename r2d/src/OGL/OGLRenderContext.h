#ifndef R2D_OGL_RENDER_CONTEXT_H
#define R2D_OGL_RENDER_CONTEXT_H

namespace R2D {
	class OglRenderContext {
		bool InitOGL();
		bool DeinitOGL();
	public:
		OglRenderContext();
		virtual ~OglRenderContext();
		bool Init();
		bool Deinit();
		virtual void ApplyCamera(const ICamera& camera);
		virtual bool BeginScene();
		virtual bool EndScene();
		virtual void RenderPoint(vec2 point, ivec3 color = ivec3(0xFF, 0xFF, 0xFF), float pointSize = 1.0f);
		virtual void RenderLine(vec2 point1, vec2 point2, ivec3 color = ivec3(0xFF, 0xFF, 0xFF));
		virtual void RenderWorldAxises(const matrix44& transform);
	};
}

#endif