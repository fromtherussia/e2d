#include "Types.h"

#include "GeometryUtils.h"
#include "Rect.h"
#include "Polygon.h"

// Private

bool Polygon2d::Validate(const Vertecies& vertecies) {
	return true;
}

// Public

Polygon2d::Polygon2d(const Vertecies& vertecies) {
	if (!Validate(vertecies)) {
		throw std::logic_error("invalid polygon");
	}
	m_vertecies = vertecies;
}

Polygon2d::Polygon2d(const Rect& rect) {
	if (!rect.Validate()) {
		throw std::logic_error("invalid rectangle");
	}
	*this << vec2(rect.x1, rect.y1) << vec2(rect.x2, rect.y1) << vec2(rect.x2, rect.y2) << vec2(rect.x1, rect.y2);
}

Polygon2d::~Polygon2d() {

}

Polygon2d& Polygon2d::operator <<(const vec2& vertex) {
	m_vertecies.push_back(vertex);
	if (!Validate(m_vertecies)) {
		m_vertecies.pop_back();
		throw std::logic_error("invalid polygon");
	}
	return *this;
}

Polygon2d& Polygon2d::operator <<(vec2& vertex) {
	m_vertecies.push_back(vertex);
	if (!Validate(m_vertecies)) {
		m_vertecies.pop_back();
		throw std::logic_error("invalid polygon");
	}
	return *this;
}

Polygon2d& Polygon2d::InsertVertex(uint pos, const vec2& vertex) {
	Vertecies::iterator verteciesIt = m_vertecies.begin();
	for (uint i = 0; i < pos; ++i) {
		verteciesIt++;
	}
	m_vertecies.insert(verteciesIt, vertex);
	return *this;
}

Polygon2d& Polygon2d::RemoveVertex(uint pos) {
	Vertecies::iterator verteciesIt = m_vertecies.begin();
	for (uint i = 0; i < pos; ++i) {
		verteciesIt++;
	}
	m_vertecies.erase(verteciesIt);
	return *this;
}

bool Polygon2d::IsIntersects(const vec2& vertex, float threshold) const {
	for (size_t i = 1; i < m_vertecies.size() - 1; ++i) {
		if (isPointInTriangle(m_vertecies[i], m_vertecies[i + 1], m_vertecies[0], vertex, threshold)) {
			return true;
		}
	}
	return false;
}

Vertecies& Polygon2d::GetVertecies() {
	return m_vertecies;
}

const Vertecies& Polygon2d::GetVertecies() const {
	return m_vertecies;
}

const vec2& Polygon2d::operator[] (uint no) const {
	return m_vertecies[no];
}

Polygon2d& Polygon2d::operator +=(const vec2& vertex) {
	for (size_t i = 0; i < m_vertecies.size(); ++i) {
		m_vertecies[i] += vertex;
	}
	return *this;
}

uint Polygon2d::VerteciesCount() const {
	return m_vertecies.size();
}

Rect Polygon2d::GetBoundingRect() const {
	if (m_vertecies.size() == 0) {
		return Rect();
	}
	
	Rect boundingRect(m_vertecies[0].x, m_vertecies[0].y, m_vertecies[0].x, m_vertecies[0].y);
	for (size_t i = 0; i < m_vertecies.size(); ++i) {
		boundingRect.x1 = glm::min(boundingRect.x1, m_vertecies[i].x);
		boundingRect.y1 = glm::min(boundingRect.y1, m_vertecies[i].y);
		boundingRect.x2 = glm::max(boundingRect.x2, m_vertecies[i].x);
		boundingRect.y2 = glm::max(boundingRect.y2, m_vertecies[i].y);
	}
	return boundingRect;
}

vec2 Polygon2d::GetCenter() const {
	if (m_vertecies.size() == 0) {
		return vec2();
	}
	
	return GetBoundingRect().Center();
}

vec2 Polygon2d::Center() {
	vec2 center = GetCenter();
	for (size_t i = 0; i < m_vertecies.size(); ++i) {
		m_vertecies[i] -= center;
	}
	return center;
}