#ifndef EDITOR_POLYGON_GRAPHIC_PRIMITIVE_EDITOR_H
#define EDITOR_POLYGON_GRAPHIC_PRIMITIVE_EDITOR_H

class PolygonGraphicPrimitiveEditor: public IVisualEditor {
	PolygonEditor m_polygonEditor;
	RectangleEditor m_textureChoordEditor;
	r2d::D3DStaticPolygon* m_polygon;
	Rect m_textureChoordRect;
	bool m_isEditGeometry;
	bool m_needUpdateGp;
	void UpdateUv();
public:
	PolygonGraphicPrimitiveEditor();
	void SetPolygon(r2d::D3DStaticPolygon* polygon);

	virtual void HandleLeftPress(const vec2& pos);
	virtual void HandleLeftRelease(const vec2& pos);
	virtual bool HandleLeftDoubleClick(const vec2& pos);
	virtual bool HandlePositionChange(const vec2& pos, const vec2& delta);
	virtual bool HandleKeyPress(KeyboardKey::Key key);
	virtual void HandleKeyRelease(KeyboardKey::Key key) {};
	virtual void Render(r2d::D3DRenderContext& context);
};

#endif