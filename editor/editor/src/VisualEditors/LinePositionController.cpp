#include <r2d/r2d.h>

#include "IVisualEditor.h"

#include "LinePositionController.h"

LinePositionController::LinePositionController(vec2* point1, vec2* point2, float threshold):
	m_point1(point1),
	m_point2(point2),
	m_threshold(threshold) {
}

bool LinePositionController::InCursor(const vec2& cursor) const {
	vec2 delta1 = (*m_point1) - cursor;
	vec2 delta2 = (*m_point2) - cursor;
	vec2 delta3 = (*m_point1) - (*m_point2);
	return glm::abs(glm::length(delta1) + glm::length(delta2) - glm::length(delta3)) <= m_threshold;
}

void LinePositionController::HandleMouseMove(const vec2& pos, const vec2& delta) {
	*m_point1 += delta;
	*m_point2 += delta;
}

void LinePositionController::Render(r2d::D3DRenderContext& context) {
	context.RenderLine(*m_point1, *m_point2, IsActive() ? COLOR_SELECTED : IsFocused() ? COLOR_FOCUSED : COLOR_REGULAR);
}