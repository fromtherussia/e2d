#include "Types.h"

#include "GeometryUtils.h"
#include "Rect.h"
#include "Polygon.h"

Polygon2d::Polygon2d() {
}

Polygon2d::Polygon2d(const Rect& rect) {
	if (!rect.Validate()) {
		throw std::logic_error("invalid rectangle");
	}
	*this << vec2(rect.x1, rect.y1) << vec2(rect.x2, rect.y1) << vec2(rect.x2, rect.y2) << vec2(rect.x1, rect.y2);
}

bool Polygon2d::IsIntersects(const vec2& vertex, float threshold) const {
	for (size_t i = 1; i < m_vertecies.size() - 1; ++i) {
		if (isPointInTriangle(m_vertecies[i], m_vertecies[i + 1], m_vertecies[0], vertex, threshold)) {
			return true;
		}
	}
	return false;
}

bool Polygon2d::Validate(const Vertecies& vertecies) {
	return true;
}