#ifndef CGL_TYPES_PARSER_H
#define CGL_TYPES_PARSER_H

#include "Types.h"

typedef RectTy<vec2> Rect;

namespace CglTypes {
	enum Type {
		ctInvalid,
		ctUnknown,
		ctBool,
		ctInt,
		ctFloat,
		ctRect,
		ctVec2,
		ctVec3,
		ctVec4,
		ctMat22,
		ctMat33,
		ctMat44
	};
}

/*
	Usage:
		1. type = GetType()
		2. if type != ctInvalid && type != ctUnknown -> switch(type)

	Throwing exceptions if type invalid
*/
class TypesParser {
public:
	static CglTypes::Type GetType(const string_t& str);
	static bool ParseBool(const string_t& str);
	static int ParseInt(const string_t& str);
	static float ParseFloat(const string_t& str);
	static Rect ParseRect(const string_t& str);
	static vec2 ParseVec2(const string_t& str);
	static vec3 ParseVec3(const string_t& str);
	static vec4 ParseVec4(const string_t& str);
	static matrix22 ParseMat22(const string_t& str);
	static matrix33 ParseMat33(const string_t& str);
	static matrix44 ParseMat44(const string_t& str);

private:
	static string_t GetStringValue(const string_t& str);
	static bool ToBool(const string_t& str);
	static int ToInt(const string_t& str);
	static float ToFloat(const string_t& str);
	static Rect ToRect(const string_t& str);
	static vec2 ToVec2(const string_t& str);
	static vec3 ToVec3(const string_t& str);
	static vec4 ToVec4(const string_t& str);
};

#endif