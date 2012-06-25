#ifndef EDITOR_CURSOR_MOVEMENT_MODIFIER_H
#define EDITOR_CURSOR_MOVEMENT_MODIFIER_H

class CursorMovementModifier {
	bool m_useGrid;
	float m_gridSize;
	bool m_isShiftPressed;
	bool m_isCtrlPressed;
	float SnapToGrid(float choord);
public:
	CursorMovementModifier();
	void SetGridSize(float gridSize);
	void TurnOnGrid();
	void TurnOffGrid();
	bool IsGridOn();
	void HandleKeyPress(KeyboardKey::Key key);
	void HandleKeyRelease(KeyboardKey::Key key);
	void ModifyCursorPos(vec2& pos);
	void ModifyCursorDelta(vec2& delta);
	void Render(r2d::D3DRenderContext& context, const R2D::D3DCamera& camera);
};

#endif