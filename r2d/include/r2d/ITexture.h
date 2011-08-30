#ifndef R2D_ITEXTURE_H
#define R2D_ITEXTURE_H

#include "Common.h"

namespace r2d {
	class ITexture {
	public:
		ITexture() {};
		virtual ~ITexture() {};
	};
	DEFPTR(ITexture);
	typedef std::vector<ITexturePtr> ITexturePtrArray;
}

#endif