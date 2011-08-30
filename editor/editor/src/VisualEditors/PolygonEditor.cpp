#include <r2d/r2d.h>

#include "IVisualEditor.h"
#include "PointPositionController.h"
#include "LinePositionController.h"

#include "PolygonEditor.h"

PolygonEditor::PolygonEditor():
	m_pointControllerIndex(-1),
	m_lineControllerIndex(-1),
	m_isDragging(false) {
}

void PolygonEditor::SetPolygon(Polygon2d* editablePolygon) {
	m_pointControllers.clear();
	m_lineControllers.clear();
	Vertecies& polygonVertecies = editablePolygon->GetVertecies();
	for (size_t i = 0; i < polygonVertecies.size(); ++i) {
		m_pointControllers.push_back(PointPositionController(&(polygonVertecies[i]), POINT_SELECTION_RADIUS));
		if (i < polygonVertecies.size() - 1) {
			m_lineControllers.push_back(LinePositionController(&(polygonVertecies[i]), &(polygonVertecies[i + 1]), LINE_SELECTION_THRESHOLD));
		}
	}
	if (polygonVertecies.size() > 1) {
		m_lineControllers.push_back(LinePositionController(&(polygonVertecies[polygonVertecies.size() - 1]), &(polygonVertecies[0]), LINE_SELECTION_THRESHOLD));
	}
	m_polygon = editablePolygon;
}

void PolygonEditor::HandleLeftPress(const vec2& pos) {
	m_pointControllerIndex = -1;
	for (size_t i = 0; i < m_pointControllers.size(); ++i) {
		if (m_pointControllers[i].InCursor(pos)) {
			m_pointControllerIndex = i;
			m_pointControllers[m_pointControllerIndex].SetActive(true);
			return;
		}
	}
	m_lineControllerIndex = -1;
	for (size_t i = 0; i < m_lineControllers.size(); ++i) {
		if (m_lineControllers[i].InCursor(pos)) {
			m_lineControllerIndex = i;
			m_lineControllers[m_lineControllerIndex].SetActive(true);
			return;
		}
	}
	if (m_polygon->IsIntersects(pos, POLYGON_SELECTION_THRESHOLD)) {
		m_isDragging = true;
	}
}

void PolygonEditor::HandleLeftRelease(const vec2& pos) {
	if (m_pointControllerIndex != -1) {
		m_pointControllers[m_pointControllerIndex].SetActive(false);
		m_pointControllerIndex = -1;
	}
	if (m_lineControllerIndex != -1) {
		m_lineControllers[m_lineControllerIndex].SetActive(false);
		m_lineControllerIndex = -1;
	}
	m_isDragging = false;
}

bool PolygonEditor::HandleLeftDoubleClick(const vec2& pos) {
	size_t lineIndex = -1;
	for (size_t i = 0; i < m_lineControllers.size(); ++i) {
		if (m_lineControllers[i].InCursor(pos)) {
			lineIndex = i;
			break;
		}
	}
	if (lineIndex != -1) {
		m_polygon->InsertVertex(lineIndex + 1, pos);
		SetPolygon(m_polygon);
		return true;
	}
	return false;
}

bool PolygonEditor::HandlePositionChange(const vec2& pos, const vec2& delta) {
	for (size_t i = 0; i < m_pointControllers.size(); ++i) {
		m_pointControllers[i].SetFocused(m_pointControllers[i].InCursor(pos));
	}
	for (size_t i = 0; i < m_lineControllers.size(); ++i) {
		m_lineControllers[i].SetFocused(m_lineControllers[i].InCursor(pos));
	}
	bool changed = false;
	if (m_pointControllerIndex != -1) {
		m_pointControllers[m_pointControllerIndex].HandleMouseMove(pos, delta);
		changed = true;
	} else if (m_lineControllerIndex != -1) {
		m_lineControllers[m_lineControllerIndex].HandleMouseMove(pos, delta);
		changed = true;
	} else if (m_isDragging) {
		*m_polygon += delta;
		changed = true;
	}
	return changed;
}

bool PolygonEditor::HandleKeyPress(KeyboardKey::Key key) {
	if (key == KeyboardKey::Delete) {
		size_t pointIndex = -1;
		for (size_t i = 0; i < m_pointControllers.size(); ++i) {
			if (m_pointControllers[i].IsFocused()) {
				pointIndex = i;
				break;
			}
		}
		if (pointIndex != -1) {
			m_polygon->RemoveVertex(pointIndex);
			SetPolygon(m_polygon);
			return true;
		}
	}
	return false;
}
/*
void PolygonEditor::HandleKeyPress(KeyboardKey::Key key) {
	if (m_pointControllerIndex != -1) {
		m_pointControllers[m_pointControllerIndex].HandleKeyPress(key);
	}
	if (m_lineControllerIndex != -1) {
		m_lineControllers[m_lineControllerIndex].HandleKeyPress(key);
	}
}

void PolygonEditor::HandleKeyRelease(KeyboardKey::Key key) {
	if (m_pointControllerIndex != -1) {
		m_pointControllers[m_pointControllerIndex].HandleKeyRelease(key);
	}
	if (m_lineControllerIndex != -1) {
		m_lineControllers[m_lineControllerIndex].HandleKeyRelease(key);
	}
}*/

void PolygonEditor::Render(r2d::D3DRenderContext& context) {
	for (size_t i = 0; i < m_pointControllers.size(); ++i) {
		m_pointControllers[i].Render(context);
	}
	for (size_t i = 0; i < m_lineControllers.size(); ++i) {
		m_lineControllers[i].Render(context);
	}
}