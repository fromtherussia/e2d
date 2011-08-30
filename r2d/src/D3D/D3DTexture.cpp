#include "IRenderContext.h"

#include "D3DCommon.h"
#include "D3DRenderContext.h"
#include "D3DTexture.h"

namespace r2d {
	D3DTexture::D3DTexture(D3DRenderContext& context, D3DFORMAT format, uint width, uint height, uint mipmapLevels, DWORD usage) {
		if (mipmapLevels > 0) {
			usage = usage | D3DUSAGE_AUTOGENMIPMAP;
		}

		HRESULT creationResult = context.GetDevice()->CreateTexture(
			width,
			height,
			mipmapLevels,
			usage,
			format,
			D3DPOOL_DEFAULT,
			&m_texture,
			NULL
		);

		if (creationResult != D3D_OK) {
			throw std::logic_error("can't create texture");
		}
	}

	D3DTexture::D3DTexture(D3DRenderContext& context, const string_t& path) {
		if (D3DXCreateTextureFromFileA(context.GetDevice(), path.c_str(), &m_texture) != D3D_OK) {
			throw std::logic_error("can't create texture");
		}
	}

	D3DTexture::~D3DTexture() {
		m_texture->Release();
	}

	LPDIRECT3DTEXTURE9 D3DTexture::GetTexture() const {
		return m_texture;
	}
} 
