#pragma once
#include "math.h"

struct Color
{
	static Color Black();
	static Color White();

	Color(float r, float g, float b);
	Color() = default;

	Color& operator +=(const Color& other);
	Color& operator /=(float other);
	
	float r, g, b;
};

Color operator*(const Color& left, float right);
Color operator*(const Color& left, const Color& right);