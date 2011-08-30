#include <r2d/r2d.h>

#include "IVisualEditor.h"
#include "PointPositionController.h"
#include "LinePositionController.h"
#include "PolygonEditor.h"
#include "RectangleEditor.h"

#include "RectGraphicPrimitiveEditor.h"

// Private 

void RectGraphicPrimitiveEditor::UpdateUv() {
	Rect boundingRect = m_rectangle->GetGeometry();
	Rect uv;
	uv.x1 = (boundingRect.x1 - m_textureChoordRect.x1) / m_textureChoordRect.Width();
	uv.y1 = (boundingRect.y1 - m_textureChoordRect.y1) / m_textureChoordRect.Height();
	uv.x2 = (boundingRect.x2 - m_textureChoordRect.x1) / m_textureChoordRect.Width();
	uv.y2 = (boundingRect.y2 - m_textureChoordRect.y1) / m_textureChoordRect.Height();
	m_rectangle->GetUv() = uv;
	m_needUpdateGp = true;
}

// Public

RectGraphicPrimitiveEditor::RectGraphicPrimitiveEditor():
	m_isEditGeometry(true),
	m_needUpdateGp(false) {
}

void RectGraphicPrimitiveEditor::SetRectangle(r2d::D3DStaticRectangle* rectangle) {
	m_textureChoordRect = rectangle->GetGeometry();
	m_rectangleEditor.SetRectangle(&(rectangle->GetGeometry()));
	m_textureChoordEditor.SetRectangle(&m_textureChoordRect);
	m_rectangle = rectangle;
}

void RectGraphicPrimitiveEditor::HandleLeftPress(const vec2& pos) {
	if (m_isEditGeometry) {
		m_rectangleEditor.HandleLeftPress(pos);
	} else {
		m_textureChoordEditor.HandleLeftPress(pos);
	}
}

void RectGraphicPrimitiveEditor::HandleLeftRelease(const vec2& pos) {
	if (m_isEditGeometry) {
		m_rectangleEditor.HandleLeftRelease(pos);
	} else {
		m_textureChoordEditor.HandleLeftRelease(pos);
	}
}

bool RectGraphicPrimitiveEditor::HandleLeftDoubleClick(const vec2& pos) {
	if (m_isEditGeometry) {
		if (!m_rectangleEditor.HandleLeftDoubleClick(pos)) {
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

bool RectGraphicPrimitiveEditor::HandlePositionChange(const vec2& pos, const vec2& delta) {
	if (m_isEditGeometry) {
		if (!m_rectangleEditor.HandlePositionChange(pos, delta)) {
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

bool RectGraphicPrimitiveEditor::HandleKeyPress(KeyboardKey::Key key) {
	switch (key) {
		case KeyboardKey::Key_T:
			m_isEditGeometry = !m_isEditGeometry;
			break;
	}
	if (m_isEditGeometry) {
		if (!m_rectangleEditor.HandleKeyPress(key)) {
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

void RectGraphicPrimitiveEditor::Render(r2d::D3DRenderContext& context) {
	if (m_isEditGeometry) {
		m_rectangleEditor.Render(context);
	} else {
		m_textureChoordEditor.Render(context);
	}
	context.RenderRectangle(m_textureChoordRect, COLOR_BORDER);
	if (m_needUpdateGp) {
		m_rectangle->SynchronizeWithGp();
		m_needUpdateGp = false;
	}
}