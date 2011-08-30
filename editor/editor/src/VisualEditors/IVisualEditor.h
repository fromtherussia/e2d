#ifndef EDITOR_IVISUAL_EDITOR_H
#define EDITOR_IVISUAL_EDITOR_H

#define COLOR_SELECTED ivec3(0, 0xFF, 0)
#define COLOR_REGULAR ivec3(0xFF, 0xFF, 0xFF)
#define COLOR_FOCUSED ivec3(0xFF, 0xFF, 0x00)
#define COLOR_BORDER ivec3(0xFF, 0, 0)

#define GRID_COLOR ivec3(0x33, 0x33, 0x33)

#define POINT_SELECTION_RADIUS 5.0f
#define LINE_SELECTION_THRESHOLD 2.0f
#define POLYGON_SELECTION_THRESHOLD 2.0f

namespace KeyboardKey {
	enum Key {
		Shift,
		Ctrl,
		Delete,
		Key_T
	};
}

class IVisualEditor {
public:
	IVisualEditor() {
	}
	virtual ~IVisualEditor() {
	}

	virtual void HandleLeftPress(const vec2& pos) = 0;
	virtual void HandleLeftRelease(const vec2& pos) = 0;
	virtual bool HandleLeftDoubleClick(const vec2& pos) = 0;
	// Returns changed state
	virtual bool HandlePositionChange(const vec2& pos, const vec2& delta) = 0;
	// Returns changed state
	virtual bool HandleKeyPress(KeyboardKey::Key key) = 0;
	virtual void HandleKeyRelease(KeyboardKey::Key key) = 0;
	virtual void Render(r2d::D3DRenderContext& context) = 0;
};

class IFocusable {
	bool m_isActive;
	bool m_isFocused;
public:
	IFocusable():
		m_isActive(false),
		m_isFocused(false) {
	}
	virtual ~IFocusable() {
	}
	//
	void SetFocused(bool isFocused) {
		m_isFocused = isFocused;
	}
	bool IsFocused() {
		return m_isFocused;
	}
	//
	void SetActive(bool isActive) {
		m_isActive = isActive;
	}
	bool IsActive() {
		return m_isActive;
	}
};

#endif