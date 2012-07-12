#include "Types.h"

#include "GeometryUtils.h"
#include "Rect.h"
#include "PolygonalChain.h"

PolygonalChain2d::PolygonalChain2d() {
}

PolygonalChain2d::PolygonalChain2d(const Vertecies& vertecies) {
	m_vertecies = vertecies;
}

PolygonalChain2d::~PolygonalChain2d() {

}

PolygonalChain2d& PolygonalChain2d::operator << (const vec2& vertex) {
	m_vertecies.push_back(vertex);
	return *this;
}

PolygonalChain2d& PolygonalChain2d::operator << (vec2& vertex) {
	m_vertecies.push_back(vertex);
	return *this;
}

PolygonalChain2d& PolygonalChain2d::InsertVertex(uint pos, const vec2& vertex) {
	Vertecies::iterator verteciesIt = m_vertecies.begin();
	for (uint i = 0; i < pos; ++i) {
		verteciesIt++;
	}
	m_vertecies.insert(verteciesIt, vertex);
	return *this;
}

PolygonalChain2d& PolygonalChain2d::RemoveVertex(uint pos) {
	Vertecies::iterator verteciesIt = m_vertecies.begin();
	for (uint i = 0; i < pos; ++i) {
		verteciesIt++;
	}
	m_vertecies.erase(verteciesIt);
	return *this;
}

Vertecies& PolygonalChain2d::GetVertecies() {
	return m_vertecies;
}

const Vertecies& PolygonalChain2d::GetVertecies() const {
	return m_vertecies;
}

const vec2& PolygonalChain2d::operator [] (uint no) const {
	return m_vertecies[no];
}

PolygonalChain2d& PolygonalChain2d::operator += (const vec2& vertex) {
	for (size_t i = 0; i < m_vertecies.size(); ++i) {
		m_vertecies[i] += vertex;
	}
	return *this;
}

uint PolygonalChain2d::VerteciesCount() const {
	return m_vertecies.size();
}

Rect PolygonalChain2d::GetBoundingRect() const {
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

vec2 PolygonalChain2d::GetCenter() const {
	if (m_vertecies.size() == 0) {
		return vec2();
	}

	return GetBoundingRect().Center();
}

vec2 PolygonalChain2d::Center() {
	vec2 center = GetCenter();
	for (size_t i = 0; i < m_vertecies.size(); ++i) {
		m_vertecies[i] -= center;
	}
	return center;
}