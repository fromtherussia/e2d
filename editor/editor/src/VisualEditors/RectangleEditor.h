#ifndef EDITOR_RECTANGLE_EDITOR_H
#define EDITOR_RECTANGLE_EDITOR_H

class RectangleEditor: public IVisualEditor {
	PointPositionControllers m_pointControllers;
	int m_pointControllerIndex;
	int m_lineControllerIndex;
	bool m_isDragging;
	vec2 m_vertecies[2];
	Rect* m_rectangle;

	void UpdateRectangle();
public:
	RectangleEditor();
	~RectangleEditor();
	void SetRectangle(Rect* rectangle);

	virtual void HandleLeftPress(const vec2& pos);
	virtual void HandleLeftRelease(const vec2& pos);
	virtual bool HandleLeftDoubleClick(const vec2& pos) { return false; }
	virtual bool HandlePositionChange(const vec2& pos, const vec2& delta);
	virtual bool HandleKeyPress(KeyboardKey::Key key) { return false; }
	virtual void HandleKeyRelease(KeyboardKey::Key key) {}
	virtual void Render(r2d::D3DRenderContext& context);
};

#endif