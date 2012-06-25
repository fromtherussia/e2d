#include <r2d/r2d.h>

#include "IVisualEditor.h"

#include "CursorMovementModifier.h"

// Private

float CursorMovementModifier::SnapToGrid(float choord) {
	return ((int)(choord / m_gridSize + 0.5f)) * m_gridSize;
}

// Public

CursorMovementModifier::CursorMovementModifier():
	m_useGrid(false),
	m_gridSize(false),
	m_isShiftPressed(false),
	m_isCtrlPressed(false) {

}

void CursorMovementModifier::SetGridSize(float gridSize) {
	m_gridSize = gridSize;
}

void CursorMovementModifier::TurnOnGrid() {
	m_useGrid = true;
}

void CursorMovementModifier::TurnOffGrid() {
	m_useGrid = false;
}

bool CursorMovementModifier::IsGridOn() {
	return m_useGrid;
}

void CursorMovementModifier::HandleKeyPress(KeyboardKey::Key key) {
	if (key == KeyboardKey::Shift) {
		m_isShiftPressed = true;
	}
	if (key == KeyboardKey::Ctrl) {
		m_isCtrlPressed = true;
	}
}

void CursorMovementModifier::HandleKeyRelease(KeyboardKey::Key key) {
	if (key == KeyboardKey::Shift) {
		m_isShiftPressed = false;
	}
	if (key == KeyboardKey::Ctrl) {
		m_isCtrlPressed = false;
	}
}

void CursorMovementModifier::ModifyCursorPos(vec2& pos) {
	if (m_useGrid) {
		pos.x = SnapToGrid(pos.x);
		pos.y = SnapToGrid(pos.y);
	}
}

void CursorMovementModifier::ModifyCursorDelta(vec2& delta) {
	if (m_useGrid) {
		delta.x = ((int)delta.x / m_gridSize) * m_gridSize;
		delta.y = ((int)delta.y / m_gridSize) * m_gridSize;
	} else if (m_isShiftPressed) {
		delta.y = 0.0f;
	} else if (m_isCtrlPressed) {
		delta.x = 0.0f;
	}
}

void CursorMovementModifier::Render(r2d::D3DRenderContext& context, const r2d::D3DCamera& camera) {
	if (m_useGrid) {
		Rect cameraRect = camera.GetVisibleRect();
		cameraRect.x1 = SnapToGrid(cameraRect.x1);
		cameraRect.x2 = SnapToGrid(cameraRect.x2);
		cameraRect.y1 = SnapToGrid(cameraRect.y1);
		cameraRect.y2 = SnapToGrid(cameraRect.y2);
		for (float x = cameraRect.x1; x < cameraRect.x2; x += m_gridSize) {
			context.RenderLine(vec2(x, cameraRect.y1), vec2(x, cameraRect.y2), GRID_COLOR);
		}
		for (float y = cameraRect.y1; y < cameraRect.y2; y += m_gridSize) {
			context.RenderLine(vec2(cameraRect.x1, y), vec2(cameraRect.x2, y), GRID_COLOR);
		}
	}
}