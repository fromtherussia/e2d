#include "Types.h"

bool isPointInTriangle(const vec2& a, const vec2& b, const vec2& c, const vec2& point, float threshold) {
	float s = glm::length(glm::cross(vec3(b - a, 0.0f), vec3(c - a, 0.0f))) * 0.5f;
	float s0 = glm::length(glm::cross(vec3(a - point, 0.0f), vec3(b - point, 0.0f))) * 0.5f;
	float s1 = glm::length(glm::cross(vec3(b - point, 0.0f), vec3(c - point, 0.0f))) * 0.5f;
	float s2 = glm::length(glm::cross(vec3(c - point, 0.0f), vec3(a - point, 0.0f))) * 0.5f;
	return glm::abs(s0 + s1 + s2 - s) <= threshold;
}