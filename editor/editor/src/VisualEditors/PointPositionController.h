#ifndef EDITOR_POINT_POSITION_CONTROLLER_H
#define EDITOR_POINT_POSITION_CONTROLLER_H

class PointPositionController: public IFocusable {
	vec2* m_point;
	Circle m_pointVicinity;
	
	void SetOrigin(const vec2& origin);
public:
	PointPositionController(vec2* point, float radius);
	
	bool InCursor(const vec2& cursor) const;
	virtual void HandleMouseMove(const vec2& pos, const vec2& delta);
	virtual void Render(r2d::D3DRenderContext& context);
};
typedef std::vector<PointPositionController> PointPositionControllers;

#endif