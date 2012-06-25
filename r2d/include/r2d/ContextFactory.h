#ifndef R2D_CONTEXT_FACTORY_H
#define R2D_CONTEXT_FACTORY_H

#include "r2d/Common.h"

namespace r2d {
	PREDECL_CLASS_WITH_PTR(IRenderContext);
	std::auto_ptr<IRenderContext> CreateRenderContext(HWND window);
}

#endif