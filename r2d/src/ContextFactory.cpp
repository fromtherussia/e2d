#include <windows.h>

#include "r2d/ContextFactory.h"

#include "r2d/D3D/D3DCommon.h"
#include "r2d/D3D/D3DRenderContext.h"

namespace r2d {
	std::auto_ptr<IRenderContext> CreateRenderContext(HWND window) {
		return std::auto_ptr<IRenderContext>(new D3DRenderContext(window));
	}
}