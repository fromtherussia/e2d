#include "../Common.h"

#include "OGLCommon.h"
#include "OGLRenderContext.h"

namespace R2D
{
	OglRenderContext::OglRenderContext() {
	}

	OglRenderContext::~OglRenderContext() {
	}

	bool OglRenderContext::Init() {
		return InitOGL();
	}

	bool OglRenderContext::Deinit() {
		return DeinitOGL();
	}

	bool OglRenderContext::InitOGL() {
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		return true;
	}

	bool OglRenderContext::DeinitOGL() {
		return true;
	}

	void OglRenderContext::ApplyCamera(const ICamera& camera) {
	}

	bool OglRenderContext::BeginScene() {
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return true;
	}

	bool OglRenderContext::EndScene() {
		glLoadIdentity();
		//SwapBuffers(hDC);
		return true;
	}

	void OglRenderContext::RenderPoint(vec2 point, ivec3 color, float pointSize) {
		glPointSize (5.0f);
		glColor3i(color.x, color.y, color.z);
		glBegin(GL_POINTS);
		glVertex2f(point.x, point.y);
		glEnd();
		glColor3i(0xFF, 0xFF, 0xFF);
		glPointSize (1.0f);
	}

	void OglRenderContext::RenderLine(vec2 point1, vec2 point2, ivec3 color) {
		glColor3i(color.x, color.y, color.z);
		glBegin(GL_LINES);
		glVertex2f(point1.x, point1.y);
		glVertex2f(point2.x, point2.y);
		glEnd();
		glColor3i(0xFF, 0xFF, 0xFF);
	}

	void OglRenderContext::RenderWorldAxises(const matrix44& transform) {
	}
}