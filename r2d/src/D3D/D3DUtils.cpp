#include "D3DCommon.h"

#include "D3DUtils.h"

namespace r2d {
	matrix44 ToMatrix44(const D3DXMATRIXA16& matrix) {
		return matrix44();
	}

	D3DXMATRIXA16 ToMatrixD3D(const matrix44& matrix) {
		D3DXMATRIXA16 result;
		return result;
	}

	D3DXMATRIXA16 ToMatrixD3D(vec2 position, float angle) {
		D3DXMATRIXA16 transform;
		D3DXMATRIXA16 newTranslation;
		D3DXMATRIXA16 newRotation;
		
		D3DXMatrixTranslation(&newTranslation, position.x, position.y, 0.0f);
		D3DXMatrixRotationZ(&newRotation, angle);
		
		D3DXMatrixMultiply(&transform, &newRotation, &newTranslation);

		return transform;
	}
}
