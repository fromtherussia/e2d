#include "r2d/IRenderContext.h"

#include "r2d/D3D/D3DCommon.h"
#include "r2d/D3D/D3DRenderContext.h"
#include "r2d/D3D/D3DFont.h"

namespace r2d {
	D3DFont::D3DFont(D3DRenderContext& context, const FontAttributes& fontAttributes) {
		HRESULT result = D3DXCreateFontA(
			context.GetDevice(),
			fontAttributes.m_height,
			fontAttributes.m_width,
			fontAttributes.m_weight,
			1,
			fontAttributes.m_isItalic,
			fontAttributes.m_charset,
			fontAttributes.m_precision,
			fontAttributes.m_quality,
			fontAttributes.m_familyIndex,
			fontAttributes.m_fontFace.c_str(),
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

	void D3DFont::Render(D3DRenderContext& context, const Rect& cameraRect, const string_t& text, const vec2& pos, const ivec3& color, VerticalAlign::Align verticalAlign, HorisontalAlign::Align horisontalAlign, const vec2& padding) {
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

	void D3DFont::RenderContrast(D3DRenderContext& context, const Rect& cameraRect, const string_t& text, const vec2& pos, const ivec3& color1, const ivec3& color2, VerticalAlign::Align verticalAlign, HorisontalAlign::Align horisontalAlign, const vec2& padding) {
		Render(context, cameraRect, text, pos + vec2(1.0f, -1.0f), color2, verticalAlign, horisontalAlign, padding);
		Render(context, cameraRect, text, pos, color1, verticalAlign, horisontalAlign, padding);
	}

}