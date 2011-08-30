#ifndef CGL_UTILS_H
#define CGL_UTILS_H

#include "Types.h"

string_t formatString(char* format, ...);
string_t vec2ToString(vec2 vec);
string_t floatToString(float val);

float roundToMin(float val, int step);
float roundToMax(float val, int step);

#endif