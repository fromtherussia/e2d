#ifndef EDITOR_DEBUG_RENDERER_H
#define EDITOR_DEBUG_RENDERER_H

const vec2 TEXT_PADDING(5.0f, 2.0f);

const ivec3 BOUNDARIES_RULES(0x22, 0x22, 0x22);
const ivec3 BOUNDARIES_COLOR(0x44, 0x44, 0x44);
const ivec3 BOUNDARIES_HIGHLIGHT(0xFF, 0xFF, 0xFF);
const float BOUNDARIES_CENTER_LINE_LENGTH = 5.0f;
const float BOUNDARIES_INNER_LINE_LENGTH = 10.0f;
const ivec3 BOUNDARIES_NUMBERS_COLOR(0xFF, 0xFF, 0xFF);
const ivec3 BOUNDARIES_NUMBERS_COLOR_CONTRAST(0, 0, 0);

const ivec3 RULES_SMALL_COLOR(0x88, 0x88, 0x88);
const ivec3 RULES_LARGE_COLOR(0x22, 0x22, 0x22);
const ivec3 RULES_BACKGROUND_COLOR(0xCC, 0xCC, 0xCC);
const float RULES_SMALL_LINE_LENGTH = 5.0f;
const float RULES_LARGE_LINE_LENGTH = 10.0f;


const ivec3 COLOR_SELECTED(0, 0xFF, 0);
const ivec3 COLOR_REGULAR(0xFF, 0xFF, 0xFF);
const ivec3 COLOR_FOCUSED(0xFF, 0xFF, 0x00);
const ivec3 COLOR_BORDER(0xFF, 0, 0);
const ivec3 GRID_COLOR(0x33, 0x33, 0x33);

const float POINT_SELECTION_RADIUS(5.0f);
const float LINE_SELECTION_THRESHOLD(2.0f);
const float POLYGON_SELECTION_THRESHOLD(2.0f);



class DebugRenderer {
	r2d::D3DRenderContext& m_context;
	r2d::D3DFont* m_dataOutputFont;
	r2d::D3DFont* m_dataOutputFontBold;
public:


	DebugRenderer(r2d::D3DRenderContext& context);
	~DebugRenderer();

	void RenderBoundaries(const Rect& boundingRect, const Rect& cameraRect);
	void RenderBoundaries(const Rect& boundingRect, const vec2& center, const Rect& cameraRect);
	void RenderRules(int step, const Rect& cameraRect);
};

#endif