#ifndef R2D_IFONT_H
#define R2D_IFONT_H

#include "r2d/Common.h"

namespace r2d {
	struct FontAttributes {
		uint m_width;
		uint m_height;
		uint m_weight;
		bool m_isItalic;
		uint m_quality;
		uint m_precision;
		uint m_charset;
		uint m_familyIndex;
		string_t m_fontFace;
	};

	class IFont {
	public:
		IFont();
		virtual ~IFont();

		virtual vec2 GetSize(const string_t& text) = 0;
		virtual void Render(D3DRenderContext& context, const Rect& cameraRect, const string_t& text, const vec2& pos, const ivec3& color = ivec3(0xFF, 0xFF, 0xFF), VerticalAlign::Align verticalAlign = VerticalAlign::Left, HorisontalAlign::Align horisontalAlign = HorisontalAlign::Bottom, const vec2& padding = vec2()) = 0;
		virtual void RenderContrast(D3DRenderContext& context, const Rect& cameraRect, const string_t& text, const vec2& pos, const ivec3& color1 = ivec3(0xFF, 0xFF, 0xFF), const ivec3& color2 = ivec3(0, 0, 0), VerticalAlign::Align verticalAlign = VerticalAlign::Left, HorisontalAlign::Align horisontalAlign = HorisontalAlign::Bottom, const vec2& padding = vec2()) = 0;
	};
}

#endif