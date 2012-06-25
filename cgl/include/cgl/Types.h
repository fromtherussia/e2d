#ifndef CGL_TYPES_H
#define CGL_TYPES_H

// std
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string.h>
#include <memory>
#include <vector>
#include <map>
#include <assert.h>

// glm
// Disabling vsprintf warining
#pragma warning(disable:4996)
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// boost
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

// cgl
#include "Exception.h"

// base types
typedef unsigned int uint;
typedef unsigned char binary_data_t;
typedef std::string string_t;
typedef std::wstring wstring_t;
typedef std::auto_ptr<std::istream> istream_ptr;

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

template <typename T2, typename T1>
inline std::auto_ptr<T2> dynamic_auto_ptr_cast(std::auto_ptr<T1>& ptr) {
	T2* p2 = dynamic_cast<T2*>(ptr.release());
	CGL_CHECK(p2 != NULL);
	return std::auto_ptr<T2>(p2);
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

#define PREDECL_STRUCT_WITH_PTR(structName) \
	struct structName;\
	DEFPTR(structName);

#define RESTRICT_COPY_CTOR(className) \
	className(const className&);

#define RESTRICT_ASSIGN_OPERATOR(className) \
	className& operator = (const className&);

#endif