#include <stdexcept>
#include <boost/algorithm/string.hpp>

#include "Rect.h"
#include "Utils.h"

#include "TypesParser.h"

using namespace std;

// Public

CglTypes::Type TypesParser::GetType(const string_t& str) {
	size_t pos = str.find('(');
	if (pos == string_t::npos || pos == 0) {
		return CglTypes::ctInvalid;
	}
	
	static bool isTypeMapSet = false;
	static map<string, CglTypes::Type> typeMap;
	if (!isTypeMapSet) {
		typeMap["bool"] = CglTypes::ctBool;
		typeMap["int"] = CglTypes::ctInt;
		typeMap["float"] = CglTypes::ctFloat;
		typeMap["rect"] = CglTypes::ctRect;
		typeMap["vec2"] = CglTypes::ctVec2;
		typeMap["vec3"] = CglTypes::ctVec3;
		typeMap["vec4"] = CglTypes::ctVec4;
		typeMap["mat22"] = CglTypes::ctMat22;
		typeMap["mat33"] = CglTypes::ctMat33;
		typeMap["mat44"] = CglTypes::ctMat44;
		isTypeMapSet = true;
	}

	string_t typeName = str.substr(0, pos);
	if (typeMap.count(typeName) == 0) {
		return CglTypes::ctUnknown;
	}
	return typeMap[typeName];
}

bool TypesParser::ParseBool(const string_t& str) {
	return ToBool(GetStringValue(str));
}

int TypesParser::ParseInt(const string_t& str) {
	return ToInt(GetStringValue(str));
}

float TypesParser::ParseFloat(const string_t& str) {
	return ToFloat(GetStringValue(str));
}

Rect TypesParser::ParseRect(const string_t& str) {
	return ToRect(GetStringValue(str));
}

vec2 TypesParser::ParseVec2(const string_t& str) {
	return ToVec2(GetStringValue(str));
}

vec3 TypesParser::ParseVec3(const string_t& str) {
	return ToVec3(GetStringValue(str));
}

vec4 TypesParser::ParseVec4(const string_t& str) {
	return ToVec4(GetStringValue(str));
}

matrix22 TypesParser::ParseMat22(const string_t& str) {
	vector<string_t> tokens;
	string value = GetStringValue(str);
	boost::split(tokens, value, boost::is_any_of(";"));

	if (tokens.size() != 2) {
		throw std::runtime_error(formatString("value '%s' of Mat22 should contain 2 sequences divided by ';', found %ld", value.c_str(), tokens.size()));
	}
	return matrix22(ToVec2(tokens[0]), ToVec2(tokens[1]));
}

matrix33 TypesParser::ParseMat33(const string_t& str) {
	vector<string_t> tokens;
	string value = GetStringValue(str);
	boost::split(tokens, value, boost::is_any_of(";"));

	if (tokens.size() != 3) {
		throw std::runtime_error(formatString("value '%s' of Mat33 should contain 3 sequences divided by ';', found %ld", value.c_str(), tokens.size()));
	}
	return matrix33(ToVec3(tokens[0]), ToVec3(tokens[1]), ToVec3(tokens[2]));
}

matrix44 TypesParser::ParseMat44(const string_t& str) {
	vector<string_t> tokens;
	string value = GetStringValue(str);
	boost::split(tokens, value, boost::is_any_of(";"));

	if (tokens.size() != 4) {
		throw std::runtime_error(formatString("value '%s' of Mat44 should contain 4 sequences divided by ';', found %ld", value.c_str(), tokens.size()));
	}
	return matrix44(ToVec4(tokens[0]), ToVec4(tokens[1]), ToVec4(tokens[2]), ToVec4(tokens[3]));
}

// Private

string_t TypesParser::GetStringValue(const string_t& str) {
	size_t openParenthesisPos = str.find('(');
	size_t closeParenthesisPos = str.find(')');
	
	// Validation
	if (closeParenthesisPos == string_t::npos || closeParenthesisPos != str.length() - 1) {
		throw std::runtime_error("invalid value format");
	}
	// pos('(') < pos(')') is a indirectly part of GetType: if ')' found in type -> switch won't work
	// pos('(') > 0, pos('(') != string_t::npos is a part of GetType
	return str.substr(openParenthesisPos + 1, closeParenthesisPos - openParenthesisPos - 1);
}

bool TypesParser::ToBool(const string_t& str) {
	if (str == "true") {
		return true;
	}
	if (str == "false") {
		return false;
	}
	throw std::runtime_error(formatString("invalid value '%s' of bool, should be true or false", str.c_str()));
}

int TypesParser::ToInt(const string_t& str) {
	return atoi(str.c_str());
}

float TypesParser::ToFloat(const string_t& str) {
	return atof(str.c_str());
}

Rect TypesParser::ToRect(const string_t& str) {
	vector<string_t> tokens;
	boost::split(tokens, str, boost::is_any_of(","));

	if (tokens.size() != 4) {
		throw std::runtime_error(formatString("sequence '%s' should contain 4 floats divided by ',', found %ld", str.c_str(), tokens.size()));
	}
	return Rect(ToFloat(tokens[0].c_str()), ToFloat(tokens[1].c_str()), ToFloat(tokens[2].c_str()), ToFloat(tokens[3].c_str()));
}

vec2 TypesParser::ToVec2(const string_t& str) {
	vector<string_t> tokens;
	boost::split(tokens, str, boost::is_any_of(","));

	if (tokens.size() != 2) {
		throw std::runtime_error(formatString("sequence '%s' should contain 2 floats divided by ',', found %ld", str.c_str(), tokens.size()));
	}
	return vec2(ToFloat(tokens[0].c_str()), ToFloat(tokens[1].c_str()));
}

vec3 TypesParser::ToVec3(const string_t& str) {
	vector<string_t> tokens;
	boost::split(tokens, str, boost::is_any_of(","));

	if (tokens.size() != 3) {
		throw std::runtime_error(formatString("sequence '%s' should contain 3 floats divided by ',', found %ld", str.c_str(), tokens.size()));
	}
	return vec3(ToFloat(tokens[0].c_str()), ToFloat(tokens[1].c_str()), ToFloat(tokens[2].c_str()));
}

vec4 TypesParser::ToVec4(const string_t& str) {
	vector<string_t> tokens;
	boost::split(tokens, str, boost::is_any_of(","));

	if (tokens.size() != 4) {
		throw std::runtime_error(formatString("sequence '%s' should contain 4 floats divided by ',', found %ld", str.c_str(), tokens.size()));
	}
	return vec4(ToFloat(tokens[0].c_str()), ToFloat(tokens[1].c_str()), ToFloat(tokens[2].c_str()), ToFloat(tokens[3].c_str()));
}