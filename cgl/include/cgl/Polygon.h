#ifndef CGL_POLYGON_H
#define CGL_POLYGON_H

#include "Types.h"

class Polygon2d {
public:
	Polygon2d(){};
	explicit Polygon2d(const Rect& rect);
	Polygon2d(const Vertecies& vertecies);
	~Polygon2d();
	Polygon2d& operator <<(const vec2& vertex);
	Polygon2d& operator <<(vec2& vertex);
	Polygon2d& InsertVertex(uint pos, const vec2& vertex);
	Polygon2d& RemoveVertex(uint pos);
	Vertecies& GetVertecies();
	const Vertecies& GetVertecies() const;
	// Корректно только для выпуклого многоугольника
	bool IsIntersects(const vec2& vertex, float threshold) const;
	const vec2& operator [](uint no) const;
	Polygon2d& operator +=(const vec2& vertex);
	size_t VerteciesCount() const;
	Rect GetBoundingRect() const;
	vec2 GetCenter() const;
	vec2 Center();

private:
	Vertecies m_vertecies;
	bool Validate(const Vertecies& vertecies);
};

#endif