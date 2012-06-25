#include "r2d/IRenderContext.h"

#include "r2d/D3D/D3DCommon.h"
#include "r2d/D3D/D3DRenderContext.h"
#include "r2d/D3D/D3DTexture.h"

namespace r2d {
	D3DTexture::D3DTexture(D3DRenderContext& renderContext, D3DFORMAT format, uint width, uint height, uint mipmapLevels, DWORD usage) {
		if (mipmapLevels > 0) {
			usage = usage | D3DUSAGE_AUTOGENMIPMAP;
		}

		HRESULT creationResult = renderContext.GetDevice()->CreateTexture(
			width,
			height,
			mipmapLevels,
			usage,
			format,
			D3DPOOL_DEFAULT,
			&m_texture,
			NULL
		);

		CGL_CHECK(creationResult == D3D_OK);
	}

	D3DTexture::D3DTexture(D3DRenderContext& renderContext, const string_t& path) {
		CGL_CHECK(D3DXCreateTextureFromFileA(renderContext.GetDevice(), path.c_str(), &m_texture) == D3D_OK);
	}

	D3DTexture::~D3DTexture() {
		m_texture->Release();
	}

	LPDIRECT3DTEXTURE9 D3DTexture::GetTexture() const {
		return m_texture;
	}
} 
