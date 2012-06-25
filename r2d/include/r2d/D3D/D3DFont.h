#ifndef R2D_D3D_FONT_H
#define R2D_D3D_FONT_H

#include "r2d/IFont.h"

namespace r2d {
	class D3DFont: public IFont {
	public:
		D3DFont(D3DRenderContext& context, const FontAttributes& fontAttributes);
		virtual ~D3DFont();
		// IFont
		virtual vec2 GetSize(const string_t& text);
		virtual void Render(D3DRenderContext& context, const Rect& cameraRect, const string_t& text, const vec2& pos, const ivec3& color, VerticalAlign::Align verticalAlign, HorisontalAlign::Align horisontalAlign, const vec2& padding);
		virtual void RenderContrast(D3DRenderContext& context, const Rect& cameraRect, const string_t& text, const vec2& pos, const ivec3& color1, const ivec3& color2, VerticalAlign::Align verticalAlign, HorisontalAlign::Align horisontalAlign, const vec2& padding);
	
	private:
		LPD3DXFONT m_font;
	};
}

#endif