#include "Vec2.hpp"
#include <cmath>

Vec2 Vec2::Zero()
{
	return {};
}

Vec2 Vec2::UnitX()
{
	return {1.0f, 0.0f};
}

Vec2 Vec2::UnitY()
{
	return {0.0f, 1.0f};
}

Vec2::Vec2(float x, float y):
	x{x}, y{y}
{}

float Vec2::squaredLength() const
{
	return dot(*this);
}

float Vec2::length() const
{
	return std::sqrt(squaredLength());
}

Vec2 Vec2::normalize() const
{
	return (*this) / length();
}

float Vec2::dot(const Vec2& other) const
{
	return x * other.x + y * other.y;
}

Vec2 operator-(const Vec2& v)
{
	return {-v.x, -v.y};
}

Vec2 operator+(const Vec2& left, const Vec2 & right)
{
	return {left.x + right.x, left.y + right.y};
}

Vec2 operator-(const Vec2& left, const Vec2& right)
{
	return {left.x - right.x, left.y - right.y};
}

Vec2 operator*(const Vec2& left, float right)
{
	return {left.x * right, left.y * right};
}

Vec2 operator/(const Vec2& left, float right)
{
	return left * (1.0f / right);
}
