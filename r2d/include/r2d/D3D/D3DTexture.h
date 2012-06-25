#ifndef R2D_D3D_TEXTURE_H
#define R2D_D3D_TEXTURE_H

#include "r2d/ITexture.h"

namespace r2d {
	class D3DTexture: public ITexture {
	public:
		D3DTexture(D3DRenderContext& renderContext, const string_t& path);
		D3DTexture(D3DRenderContext& renderContext, D3DFORMAT format, uint width, uint height, uint mipmapLevels = 0, DWORD usage = 0);
		~D3DTexture();
	
	private:
		D3DTexture(const ITexture&);
		LPDIRECT3DTEXTURE9 GetTexture() const;

		LPDIRECT3DTEXTURE9 m_texture;

		friend class D3DEffect;
		friend class D3DMaterial;
		friend class D3DDynamicGeometeryObject;
	};
}

#endif 
