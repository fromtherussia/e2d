#include "Types.h"

#include "Utils.h"

string_t formatString(char* format, ...) {
	// FIXME:
	char buffer[1024];
	va_list argList;
	va_start(argList, format);
	vsprintf_s(buffer, format, argList);
	va_end(argList);
	return buffer;
}

string_t vec2ToString(vec2 vec) {
	return formatString("(%.2f, %.2f)", vec.x, vec.y);
}

string_t floatToString(float val) {
	return formatString("%.2f", val);
}

float roundToMin(float val, int step) {
	return val - (((int)val) % step);
}

float roundToMax(float val, int step) {
	return val + step - (((int)val) % step);
}