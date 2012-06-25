#include <r2d/r2d.h>

#include "DebugRenderer.h"

DebugRenderer::DebugRenderer(r2d::D3DRenderContext& context):
	m_context(context) {
	r2d::FontAttributes fontAttributes;
	fontAttributes.height = 12;
	fontAttributes.width = 0;
	fontAttributes.weight = FW_NORMAL;
	fontAttributes.isItalic = false;
	fontAttributes.charset = DEFAULT_CHARSET;
	fontAttributes.precision = OUT_TT_ONLY_PRECIS; // OUT_TT_ONLY_PRECIS TrueType
	fontAttributes.quality = ANTIALIASED_QUALITY;
	fontAttributes.familyIndex = DEFAULT_PITCH | FF_DONTCARE;
	fontAttributes.fontFace = "Arial";
	m_dataOutputFont = new r2d::D3DFont(m_context, fontAttributes);

	fontAttributes.height = 12;
	fontAttributes.width = 0;
	fontAttributes.weight = FW_BOLD;
	fontAttributes.isItalic = false;
	fontAttributes.charset = DEFAULT_CHARSET;
	fontAttributes.precision = OUT_TT_ONLY_PRECIS; // OUT_TT_ONLY_PRECIS TrueType
	fontAttributes.quality = ANTIALIASED_QUALITY;
	fontAttributes.familyIndex = DEFAULT_PITCH | FF_DONTCARE;
	fontAttributes.fontFace = "Arial";
	m_dataOutputFontBold = new r2d::D3DFont(m_context, fontAttributes);
}

DebugRenderer::~DebugRenderer() {

}

void DebugRenderer::RenderBoundaries(const Rect& boundingRect, const Rect& cameraRect) {
	RenderBoundaries(boundingRect, boundingRect.Center(), cameraRect);
}

void DebugRenderer::RenderBoundaries(const Rect& boundingRect, const vec2& center, const Rect& cameraRect) {
	vec2 leftBottom = boundingRect.LeftBottomCorner();
	vec2 leftTop = boundingRect.LeftTopCorner();
	vec2 rightTop = boundingRect.RightTopCorner();
	vec2 bottomEdgeCenter = boundingRect.BottomEdgeCenter();
	vec2 rightEdgeCenter = boundingRect.RightEdgeCenter();

	// Направляющие из углов
	m_context.RenderLine(leftBottom, vec2(cameraRect.x1, leftBottom.y), BOUNDARIES_RULES);
	m_context.RenderLine(leftTop, vec2(leftTop.x, cameraRect.y2), BOUNDARIES_RULES);
	m_context.RenderLine(leftTop, vec2(cameraRect.x1, leftTop.y), BOUNDARIES_RULES);
	m_context.RenderLine(rightTop, vec2(rightTop.x, cameraRect.y2), BOUNDARIES_RULES);

	// Направляющие из центра
	m_context.RenderLine(center, vec2(center.x, cameraRect.y2), BOUNDARIES_RULES);
	m_context.RenderLine(center, vec2(cameraRect.x1, center.y), BOUNDARIES_RULES);

	// Ограницивающий прямоугольник
	m_context.RenderRectangle(boundingRect, BOUNDARIES_COLOR);
	
	// Внешние засечки
	m_context.RenderLine(leftBottom, leftBottom - vec2(BOUNDARIES_INNER_LINE_LENGTH, 0.0f), BOUNDARIES_HIGHLIGHT);
	m_context.RenderLine(leftBottom, leftBottom - vec2(0.0f, BOUNDARIES_INNER_LINE_LENGTH), BOUNDARIES_HIGHLIGHT);
	m_context.RenderLine(rightTop, rightTop + vec2(BOUNDARIES_INNER_LINE_LENGTH, 0.0f), BOUNDARIES_HIGHLIGHT);
	m_context.RenderLine(rightTop, rightTop + vec2(0.0f, BOUNDARIES_INNER_LINE_LENGTH), BOUNDARIES_HIGHLIGHT);
	
	// Перекрестие
	m_context.RenderLine(center - vec2(BOUNDARIES_CENTER_LINE_LENGTH, 0.0f), center + vec2(BOUNDARIES_CENTER_LINE_LENGTH, 0.0f), BOUNDARIES_HIGHLIGHT);
	m_context.RenderLine(center - vec2(0.0f, BOUNDARIES_CENTER_LINE_LENGTH), center + vec2(0.0f, BOUNDARIES_CENTER_LINE_LENGTH), BOUNDARIES_HIGHLIGHT);

	// Координаты углов
	m_dataOutputFont->RenderContrast(
		m_context,
		cameraRect, 
		vec2ToString(leftBottom), 
		leftBottom, 
		BOUNDARIES_NUMBERS_COLOR, 
		BOUNDARIES_NUMBERS_COLOR_CONTRAST, 
		VerticalAlign::Right, 
		HorisontalAlign::Top, 
		TEXT_PADDING);
	m_dataOutputFont->RenderContrast(
		m_context, 
		cameraRect, 
		vec2ToString(rightTop), 
		rightTop, 
		BOUNDARIES_NUMBERS_COLOR, 
		BOUNDARIES_NUMBERS_COLOR_CONTRAST, 
		VerticalAlign::Left, 
		HorisontalAlign::Bottom, 
		TEXT_PADDING
	);
	
	// Ширина и высота
	m_dataOutputFont->RenderContrast(
		m_context, 
		cameraRect, 
		floatToString(boundingRect.Width()), 
		bottomEdgeCenter, 
		BOUNDARIES_NUMBERS_COLOR, 
		BOUNDARIES_NUMBERS_COLOR_CONTRAST, 
		VerticalAlign::Center, 
		HorisontalAlign::Top, 
		TEXT_PADDING
	);
	m_dataOutputFont->RenderContrast(
		m_context, 
		cameraRect, 
		floatToString(boundingRect.Height()), 
		rightEdgeCenter, 
		BOUNDARIES_NUMBERS_COLOR, 
		BOUNDARIES_NUMBERS_COLOR_CONTRAST, 
		VerticalAlign::Left, 
		HorisontalAlign::Center, 
		TEXT_PADDING
	);
	
	// Центр
	m_dataOutputFont->RenderContrast(
		m_context, 
		cameraRect, 
		vec2ToString(center), 
		center, 
		BOUNDARIES_NUMBERS_COLOR, 
		BOUNDARIES_NUMBERS_COLOR_CONTRAST, 
		VerticalAlign::Left, 
		HorisontalAlign::Bottom, 
		TEXT_PADDING
	);
}

void DebugRenderer::RenderRules(int step, const Rect& cameraRect) {
	// Подложка для горизонтальной линейки
	m_context.RenderSolidPolygon(
		Polygon2d(Rect(
		cameraRect.x1,
		cameraRect.y2 - RULES_LARGE_LINE_LENGTH,
		cameraRect.x2,
		cameraRect.y2
		)),
		RULES_BACKGROUND_COLOR
	);

	// Подложка для вертикальной линейки
	m_context.RenderSolidPolygon(Polygon2d(Rect(
		cameraRect.x1,
		cameraRect.y1,
		cameraRect.x1 + RULES_LARGE_LINE_LENGTH,
		cameraRect.y2
		)), 
		RULES_BACKGROUND_COLOR
	);

	float minx = roundToMin(cameraRect.x1 + RULES_LARGE_LINE_LENGTH * 3, step);
	float maxx = roundToMax(cameraRect.x2, step);
	for (float x = minx; x <= maxx; x += step) {
		if ((((int)x) / step) % 5 == 0) {
			m_context.RenderLine(
				vec2(x, cameraRect.y2), 
				vec2(x, cameraRect.y2 - RULES_LARGE_LINE_LENGTH),
				RULES_LARGE_COLOR
			);
			m_dataOutputFont->RenderContrast(
				m_context, 
				cameraRect, 
				floatToString(x), 
				vec2(x, cameraRect.y2 - RULES_LARGE_LINE_LENGTH), 
				BOUNDARIES_NUMBERS_COLOR, 
				BOUNDARIES_NUMBERS_COLOR_CONTRAST, 
				VerticalAlign::Center, 
				HorisontalAlign::Top, 
				TEXT_PADDING
			);
		} else {
			m_context.RenderLine(
				vec2(x, cameraRect.y2), 
				vec2(x, cameraRect.y2 - RULES_SMALL_LINE_LENGTH),
				RULES_SMALL_COLOR
			);
		}
	}

	float miny = roundToMin(cameraRect.y1, step);
	float maxy = roundToMin(cameraRect.y2 - RULES_LARGE_LINE_LENGTH * 3, step);
	for (float y = miny; y <= maxy; y += step) {
		if ((((int)y) / step) % 5 == 0) {
			m_context.RenderLine(
				vec2(cameraRect.x1, y), 
				vec2(cameraRect.x1 + RULES_LARGE_LINE_LENGTH, y),
				RULES_LARGE_COLOR
			);
			m_dataOutputFont->RenderContrast(
				m_context, 
				cameraRect, 
				floatToString(y), 
				vec2(cameraRect.x1 + RULES_LARGE_LINE_LENGTH, y), 
				BOUNDARIES_NUMBERS_COLOR, 
				BOUNDARIES_NUMBERS_COLOR_CONTRAST, 
				VerticalAlign::Left, 
				HorisontalAlign::Center, 
				TEXT_PADDING
			);
		} else {
			m_context.RenderLine(
				vec2(cameraRect.x1, y), 
				vec2(cameraRect.x1 + RULES_SMALL_LINE_LENGTH, y),
				RULES_SMALL_COLOR
			);
		}
	}
}