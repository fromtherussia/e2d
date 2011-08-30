#ifndef R2D_IFONT_H
#define R2D_IFONT_H

#include "Common.h"

namespace r2d {
	struct FontAttributes {
		uint width;
		uint height;
		uint weight;
		bool isItalic;
		uint quality;
		uint precision;
		uint charset;
		uint familyIndex;
		string_t fontFace;
	};

	class IFont {
	public:
		IFont();
		~IFont();
	};
	DEFPTR(IFont);
}

#endif