#ifndef CGL_CIRCLE_H
#define CGL_CIRCLE_H

#include "Types.h"

template <typename vec2type>
class CircleTy {
public:
	typedef typename vec2type::value_type choordType;
	typedef vec2type originType;

	CircleTy(choordType radius, const vec2type& origin) {
		if (!SetRadius(radius)) {
			throw std::invalid_argument("radius < 0");
		}
		SetOrigin(origin);
	}
	
	const vec2type& GetOrigin() const {
		return m_origin;
	}

	void SetOrigin(const vec2type& origin) {
		m_origin = origin;
	}
	
	choordType GetRadius() const {
		return m_radius;
	}

	bool SetRadius(float radius) {
		if (radius < 0) {
			return false;
		}
		m_radius = radius;
		m_radiusSquared = m_radius * m_radius;
		return true;
	}
	
	bool IsIntersects (const CircleTy<vec2type>& circle) const {
		vec2type radiusVector = m_origin - circle.origin;
		return radiusVector.x * radiusVector.x + radiusVector.y * radiusVector.y < (m_radius + circle.radius) * (m_radius + circle.radius);
	}

	bool IsIntersects(choordType px, choordType py) const {
		choordType dx = m_origin.x - px;
		choordType dy = m_origin.y - py;
		return dx * dx + dy * dy < m_radiusSquared;
	}

	bool IsIntersects(const originType& point) const {
		choordType dx = m_origin.x - point.x;
		choordType dy = m_origin.y - point.y;
		return (dx * dx + dy * dy) < m_radiusSquared;
	}

	RectTy<vec2type> GetBoundingRect() const {
		return RectTy<vec2type>(m_origin.x - m_radius, m_origin.y - m_radius, m_origin.x + m_radius, m_origin.y + m_radius);
	}

	RectTy<vec2type> GetInnerRect() const {
		float innerRadius = m_radius * sqrt(2.0f);
		return RectTy<vec2type>(m_origin.x - innerRadius, m_origin.y - innerRadius, m_origin.x + innerRadius, m_origin.y + innerRadius);
	}

private:
	vec2type m_origin;
	choordType m_radius;
	choordType m_radiusSquared;
};

typedef CircleTy<ivec2> CircleI;
typedef CircleTy<vec2> Circle;

#endif