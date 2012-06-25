#ifndef EDITOR_POLYGON_EDITOR_H
#define EDITOR_POLYGON_EDITOR_H

class PolygonEditor: public IVisualEditor {
	PointPositionControllers m_pointControllers;
	LinePositionControllers m_lineControllers;
	int m_pointControllerIndex;
	int m_lineControllerIndex;
	Polygon2d* m_polygon;
	bool m_isDragging;
public:
	PolygonEditor();
	void SetPolygon(Polygon2d* editablePolygon);
	
	virtual void HandleLeftPress(const vec2& pos);
	virtual void HandleLeftRelease(const vec2& pos);
	virtual bool HandleLeftDoubleClick(const vec2& pos);
	virtual bool HandlePositionChange(const vec2& pos, const vec2& delta);
	virtual bool HandleKeyPress(KeyboardKey::Key key);
	virtual void HandleKeyRelease(KeyboardKey::Key key) {}
	virtual void Render(r2d::D3DRenderContext& context);
};

#endif