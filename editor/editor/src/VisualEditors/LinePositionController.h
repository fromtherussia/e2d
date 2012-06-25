#ifndef EDITOR_LINE_POSITION_CONTROLLER_H
#define EDITOR_LINE_POSITION_CONTROLLER_H

class LinePositionController: public IFocusable {
	vec2* m_point1;
	vec2* m_point2;
	float m_threshold;
public:
	LinePositionController(vec2* point1, vec2* point2, float threshold);
	
	bool InCursor(const vec2& cursor) const;
	virtual void HandleMouseMove(const vec2& pos, const vec2& delta);
	virtual void Render(r2d::D3DRenderContext& context);
};
typedef std::vector<LinePositionController> LinePositionControllers;

#endif