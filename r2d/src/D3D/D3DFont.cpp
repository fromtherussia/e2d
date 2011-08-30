#include "IRenderContext.h"

#include "D3DCommon.h"
#include "D3DRenderContext.h"
#include "D3DFont.h"

namespace r2d {
	
	D3DFont::D3DFont(D3DRenderContext& context, const FontAttributes& fontAttributes) {
		HRESULT result = D3DXCreateFontA(
			context.GetDevice(),
			fontAttributes.height,
			fontAttributes.width,
			fontAttributes.weight,
			1,
			fontAttributes.isItalic,
			fontAttributes.charset,
			fontAttributes.precision,
			fontAttributes.quality,
			fontAttributes.familyIndex,
			fontAttributes.fontFace.c_str(),
			&m_font
		);
		if (result != S_OK) {
			throw std::logic_error("");
		}
	}

	D3DFont::~D3DFont() {

	}

	vec2 D3DFont::GetSize(const string_t& text) {
		SIZE dimensions;
		GetTextExtentPoint32A(m_font->GetDC(), text.c_str(), text.length(), &dimensions);
		return vec2(dimensions.cx, dimensions.cy);
	}

	void D3DFont::Render(D3DRenderContext& context, const Rect& cameraRect, const string_t& text, vec2 pos, ivec3 color, VerticalAlign::Align verticalAlign, HorisontalAlign::Align horisontalAlign, vec2 padding) {
		vec2 textSize = GetSize(text);
		float x = pos.x;
		float y = pos.y;
		switch(verticalAlign) {
			case VerticalAlign::Left:
				x += padding.x;
				break;
			case VerticalAlign::Center:
				x -= textSize.x * 0.5f;
				break;
			case VerticalAlign::Right:
				x -= textSize.x + padding.x;
				break;
		}
		switch(horisontalAlign) {
			case HorisontalAlign::Bottom:
				y += padding.y;
				break;
			case VerticalAlign::Center:
				y -= textSize.y * 0.5f;
				break;
			case HorisontalAlign::Top:
				y -= textSize.y + padding.y;
				break;
		}
		vec2 cameraCenter = cameraRect.Center();
		x = x - cameraCenter.x + cameraRect.Width() * 0.5f;
		y = cameraRect.Height() * 0.5 - y + cameraCenter.y;
		RECT textRect;
		SetRect(&textRect, x, y + textSize.y, x + textSize.x, y);
		m_font->DrawTextA(
			NULL,
			text.c_str(),
			text.length(),
			&textRect,
			DT_LEFT | DT_BOTTOM | DT_NOCLIP,
			D3DCOLOR_RGBA(color.x, color.y, color.z, 0xFF)
		);
	}

	void D3DFont::RenderContrast(D3DRenderContext& context, const Rect& cameraRect, const string_t& text, vec2 pos, ivec3 color1, ivec3 color2, VerticalAlign::Align verticalAlign, HorisontalAlign::Align horisontalAlign, vec2 padding) {
		Render(context, cameraRect, text, pos + vec2(1.0f, -1.0f), color2, verticalAlign, horisontalAlign, padding);
		Render(context, cameraRect, text, pos, color1, verticalAlign, horisontalAlign, padding);
	}

}