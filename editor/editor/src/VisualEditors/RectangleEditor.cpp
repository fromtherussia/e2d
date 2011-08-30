#include <r2d/r2d.h>

#include "IVisualEditor.h"
#include "PointPositionController.h"
#include "LinePositionController.h"

#include "RectangleEditor.h"

// Private

void RectangleEditor::UpdateRectangle() {
	*m_rectangle = Rect(m_vertecies[0], m_vertecies[1]);
	m_rectangle->Normalize();
}

// Public

RectangleEditor::RectangleEditor():
	m_pointControllerIndex(-1),
	m_lineControllerIndex(-1),
	m_isDragging(false) {
}

RectangleEditor::~RectangleEditor() {

}

void RectangleEditor::SetRectangle(Rect* rectangle) {
	m_pointControllers.clear();
	
	m_vertecies[0] = vec2(rectangle->x1, rectangle->y1);
	m_vertecies[1] = vec2(rectangle->x2, rectangle->y2);
	
	for (size_t i = 0; i < 2; ++i) {
		m_pointControllers.push_back(PointPositionController(&(m_vertecies[i]), POINT_SELECTION_RADIUS));
	}
	m_rectangle = rectangle;
	m_pointControllerIndex = -1;
}

void RectangleEditor::HandleLeftPress(const vec2& pos) {
	m_pointControllerIndex = -1;
	for (size_t i = 0; i < m_pointControllers.size(); ++i) {
		if (m_pointControllers[i].InCursor(pos)) {
			m_pointControllerIndex = i;
			m_pointControllers[m_pointControllerIndex].SetActive(true);
			return;
		}
	}
	if (m_rectangle->IsIntersects(pos)) {
		m_isDragging = true;
	}
}

void RectangleEditor::HandleLeftRelease(const vec2& pos) {
	if (m_pointControllerIndex != -1) {
		m_pointControllers[m_pointControllerIndex].SetActive(false);
		m_pointControllerIndex = -1;
	}
	m_isDragging = false;
	UpdateRectangle();
}

bool RectangleEditor::HandlePositionChange(const vec2& pos, const vec2& delta) {
	for (size_t i = 0; i < m_pointControllers.size(); ++i) {
		m_pointControllers[i].SetFocused(m_pointControllers[i].InCursor(pos));
	}
	bool changed = false;
	if (m_pointControllerIndex != -1) {
		m_pointControllers[m_pointControllerIndex].HandleMouseMove(pos, delta);
		changed = true;
	} else if (m_isDragging) {
		m_vertecies[0] += delta;
		m_vertecies[1] += delta;
		changed = true;
	}
	if (changed) {
		UpdateRectangle();
	}
	return changed;
}

void RectangleEditor::Render(r2d::D3DRenderContext& context) {
	for (size_t i = 0; i < m_pointControllers.size(); ++i) {
		m_pointControllers[i].Render(context);
	}
}