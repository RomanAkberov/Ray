#include "color.hpp"

Color Color::Black()
{
	return {0.0f, 0.0f, 0.0f};
}

Color Color::White()
{
	return {1.0f, 1.0f, 1.0f};
}

Color::Color(float r, float g, float b) :
	r{r}, g{g}, b{b}
{}

Color& Color::operator+=(const Color& other)
{
	r += other.r;
	g += other.g;
	b += other.b;
	return *this;
}

Color& Color::operator/=(float s)
{
	r /= s;
	g /= s;
	b /= s;
	return *this;
}

Color operator*(const Color& left, float right)
{
	return Color(left.r * right, left.g * right, left.b * right);
}

Color operator*(const Color& left, const Color& right)
{
	return Color(left.r * right.r, left.g * right.g, left.b * right.b);
}
