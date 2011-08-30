#ifndef CGL_TYPES_H
#define CGL_TYPES_H

// std
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>
#include <iostream>
#include <math.h>
#include <string.h>
#include <vector>
#include <map>
#include <assert.h>

// glm
// Disabling vsprintf warining
#pragma warning(disable:4996)
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// boost
#include <boost/shared_ptr.hpp>

// base types
typedef unsigned int uint;
typedef unsigned char binary_data_t;
typedef std::string string_t;
typedef std::wstring wstring_t;

// vector types
typedef glm::ivec2 ivec2;
typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::ivec3 ivec3;
typedef glm::mat2x2 matrix22;
typedef glm::mat3x3 matrix33;
typedef glm::mat4x4 matrix44;

typedef std::vector<vec2> Vertecies;

template <typename T>
inline bool inRangeStrict(const T& a, const T& b, const T& v) {
	return v >= a && v <= b;
}

template <typename T>
inline bool inRangeNonStrict(const T& a, const T& b, const T& v) {
	return v > a && v < b;
}

namespace HorisontalAlign {
	enum Align {
		Bottom,
		Center,
		Top
	};
}

namespace VerticalAlign {
	enum Align {
		Left,
		Center,
		Right
	};
}

#define DEFPTR(className) typedef boost::shared_ptr<className> className##Ptr;

#define PREDECL_CLASS_WITH_PTR(className) \
	class className;\
	DEFPTR(className);

#define RESTRICT_COPY_CTOR(className) \
	className(const className&);

#define RESTRICT_ASSIGN_OPERATOR(className) \
	className& operator = (const className&);

#endif