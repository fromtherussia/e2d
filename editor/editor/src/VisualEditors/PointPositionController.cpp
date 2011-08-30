#include <r2d/r2d.h>

#include "IVisualEditor.h"

#include "PointPositionController.h"

// Private

void PointPositionController::SetOrigin(const vec2& origin) {
	m_pointVicinity.SetOrigin(origin);
	*m_point = origin;
}

// Public

PointPositionController::PointPositionController(vec2* point, float radius):
	m_point(point),
	m_pointVicinity(radius, *point) {
}

bool PointPositionController::InCursor(const vec2& cursor) const {
	return m_pointVicinity.IsIntersects(cursor);
}

void PointPositionController::Render(r2d::D3DRenderContext& context) {
	m_pointVicinity.SetOrigin(*m_point);
	context.RenderCircle(m_pointVicinity, IsActive() ? COLOR_SELECTED : IsFocused() ? COLOR_FOCUSED : COLOR_REGULAR);
}

void PointPositionController::HandleMouseMove(const vec2&, const vec2& delta) {
	SetOrigin(*m_point + delta);
}