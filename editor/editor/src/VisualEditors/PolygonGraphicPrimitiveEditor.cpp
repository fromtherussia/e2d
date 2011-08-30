#include <r2d/r2d.h>

#include "IVisualEditor.h"
#include "PointPositionController.h"
#include "LinePositionController.h"
#include "PolygonEditor.h"
#include "RectangleEditor.h"

#include "PolygonGraphicPrimitiveEditor.h"

// Private 

void PolygonGraphicPrimitiveEditor::UpdateUv() {
	Rect boundingRect = m_polygon->GetGeometry().GetBoundingRect();
	Rect uv;
	uv.x1 = (boundingRect.x1 - m_textureChoordRect.x1) / m_textureChoordRect.Width();
	uv.y1 = (boundingRect.y1 - m_textureChoordRect.y1) / m_textureChoordRect.Height();
	uv.x2 = (boundingRect.x2 - m_textureChoordRect.x1) / m_textureChoordRect.Width();
	uv.y2 = (boundingRect.y2 - m_textureChoordRect.y1) / m_textureChoordRect.Height();
	m_polygon->GetUv() = uv;
	m_needUpdateGp = true;
}

// Public

PolygonGraphicPrimitiveEditor::PolygonGraphicPrimitiveEditor():
	m_isEditGeometry(true),
	m_needUpdateGp(false) {
}

void PolygonGraphicPrimitiveEditor::SetPolygon(r2d::D3DStaticPolygon* polygon) {
	m_textureChoordRect = polygon->GetGeometry().GetBoundingRect();
	m_polygonEditor.SetPolygon(&(polygon->GetGeometry()));
	m_textureChoordEditor.SetRectangle(&m_textureChoordRect);
	m_polygon = polygon;
}

void PolygonGraphicPrimitiveEditor::HandleLeftPress(const vec2& pos) {
	if (m_isEditGeometry) {
		m_polygonEditor.HandleLeftPress(pos);
	} else {
		m_textureChoordEditor.HandleLeftPress(pos);
	}
}

void PolygonGraphicPrimitiveEditor::HandleLeftRelease(const vec2& pos) {
	if (m_isEditGeometry) {
		m_polygonEditor.HandleLeftRelease(pos);
	} else {
		m_textureChoordEditor.HandleLeftRelease(pos);
	}
}

bool PolygonGraphicPrimitiveEditor::HandleLeftDoubleClick(const vec2& pos) {
	if (m_isEditGeometry) {
		if (!m_polygonEditor.HandleLeftDoubleClick(pos)) {
			return false;
		}
	} else {
		if(!m_textureChoordEditor.HandleLeftDoubleClick(pos)) {
			return false;
		}
	}
	UpdateUv();
	return true;
}

bool PolygonGraphicPrimitiveEditor::HandlePositionChange(const vec2& pos, const vec2& delta) {
	if (m_isEditGeometry) {
		if (!m_polygonEditor.HandlePositionChange(pos, delta)) {
			return false;
		}
	} else {
		if (!m_textureChoordEditor.HandlePositionChange(pos, delta)) {
			return false;
		}
	}
	UpdateUv();
	return true;
}

bool PolygonGraphicPrimitiveEditor::HandleKeyPress(KeyboardKey::Key key) {
	switch (key) {
		case KeyboardKey::Key_T:
			m_isEditGeometry = !m_isEditGeometry;
			break;
	}
	if (m_isEditGeometry) {
		if (!m_polygonEditor.HandleKeyPress(key)) {
			return false;
		}
	} else {
		if (!m_textureChoordEditor.HandleKeyPress(key)) {
			return false;
		}
	}
	UpdateUv();
	return true;
}

void PolygonGraphicPrimitiveEditor::Render(r2d::D3DRenderContext& context) {
	if (m_isEditGeometry) {
		m_polygonEditor.Render(context);
	} else {
		m_textureChoordEditor.Render(context);
	}
	context.RenderRectangle(m_textureChoordRect, COLOR_BORDER);
	if (m_needUpdateGp) {
		m_polygon->SynchronizeWithGp();
		m_needUpdateGp = false;
	}
}