#ifndef CGL_POLYGON_H
#define CGL_POLYGON_H

#include "PolygonalChain.h"

class Polygon2d: public PolygonalChain2d {
public:
	Polygon2d();
	explicit Polygon2d(const Rect& rect);
	// Корректно только для выпуклого многоугольника
	bool IsIntersects(const vec2& vertex, float threshold) const;

private:
	bool Validate(const Vertecies& vertecies);
};

#endif