#include <windows.h>

#include "ContextFactory.h"

#include "D3DCommon.h"
#include "D3DRenderContext.h"

namespace r2d {
	IRenderContextPtr CreateRenderContext(HWND window) {
		return boost::dynamic_pointer_cast<IRenderContext>(
			D3DRenderContextPtr(new D3DRenderContext(window))
		);
	}
}