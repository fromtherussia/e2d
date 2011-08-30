#ifndef R2D_D3D_FONT_H
#define R2D_D3D_FONT_H

#include "IFont.h"

namespace r2d {
	class D3DFont: public IFont {
	public:
		D3DFont(D3DRenderContext& context, const FontAttributes& fontAttributes);
		virtual ~D3DFont();

		vec2 GetSize(const string_t& text);
		void Render(D3DRenderContext& context, const Rect& cameraRect, const string_t& text, vec2 pos, ivec3 color = ivec3(0xFF, 0xFF, 0xFF), VerticalAlign::Align verticalAlign = VerticalAlign::Left, HorisontalAlign::Align horisontalAlign = HorisontalAlign::Bottom, vec2 padding = vec2());
		void RenderContrast(D3DRenderContext& context, const Rect& cameraRect, const string_t& text, vec2 pos, ivec3 color1 = ivec3(0xFF, 0xFF, 0xFF), ivec3 color2 = ivec3(0, 0, 0), VerticalAlign::Align verticalAlign = VerticalAlign::Left, HorisontalAlign::Align horisontalAlign = HorisontalAlign::Bottom, vec2 padding = vec2());
	
	private:
		LPD3DXFONT m_font;
	};
	DEFPTR(D3DFont);
}

#endif