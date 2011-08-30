#ifndef R2D_D3D_UTILS_H
#define R2D_D3D_UTILS_H

#include "Common.h"

namespace r2d {
	matrix44 ToMatrix44 (const D3DXMATRIXA16& matrix);
	D3DXMATRIXA16 ToMatrixD3D (const matrix44& matrix);
	D3DXMATRIXA16 ToMatrixD3D(vec2 position, float angle);
}

#endif