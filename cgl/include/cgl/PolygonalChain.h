#ifndef CGL_POLYGONAL_CHAIN_H
#define CGL_POLYGONAL_CHAIN_H

#include "Types.h"

class PolygonalChain2d {
public:
	PolygonalChain2d();
	PolygonalChain2d(const Vertecies& vertecies);
	~PolygonalChain2d();
	PolygonalChain2d& operator << (const vec2& vertex);
	PolygonalChain2d& operator << (vec2& vertex);
	PolygonalChain2d& InsertVertex(uint pos, const vec2& vertex);
	PolygonalChain2d& RemoveVertex(uint pos);
	Vertecies& GetVertecies();
	const Vertecies& GetVertecies() const;
	const vec2& operator [] (uint no) const;
	PolygonalChain2d& operator += (const vec2& vertex);
	size_t VerteciesCount() const;
	Rect GetBoundingRect() const;
	vec2 GetCenter() const;
	vec2 Center();

protected:
	Vertecies m_vertecies;
};

#endif