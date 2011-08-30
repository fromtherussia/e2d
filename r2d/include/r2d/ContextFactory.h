#ifndef R2D_CONTEXT_FACTORY_H
#define R2D_CONTEXT_FACTORY_H

#include "Common.h"

namespace r2d {
	PREDECL_CLASS_WITH_PTR(IRenderContext);
	IRenderContextPtr CreateRenderContext(HWND window);
}

#endif