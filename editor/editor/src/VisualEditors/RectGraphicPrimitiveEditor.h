#ifndef EDITOR_RECT_GRAPHIC_PRIMITIVE_EDITOR_H
#define EDITOR_RECT_GRAPHIC_PRIMITIVE_EDITOR_H

class RectGraphicPrimitiveEditor: public IVisualEditor {
	RectangleEditor m_rectangleEditor;
	RectangleEditor m_textureChoordEditor;
	r2d::D3DStaticRectangle* m_rectangle;
	Rect m_textureChoordRect;
	bool m_isEditGeometry;
	bool m_needUpdateGp;
	void UpdateUv();
public:
	RectGraphicPrimitiveEditor();
	void SetRectangle(r2d::D3DStaticRectangle* rectangle);

	virtual void HandleLeftPress(const vec2& pos);
	virtual void HandleLeftRelease(const vec2& pos);
	virtual bool HandleLeftDoubleClick(const vec2& pos);
	virtual bool HandlePositionChange(const vec2& pos, const vec2& delta);
	virtual bool HandleKeyPress(KeyboardKey::Key key);
	virtual void HandleKeyRelease(KeyboardKey::Key key) {};
	virtual void Render(r2d::D3DRenderContext& context);
};

#endif