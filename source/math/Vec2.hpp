#pragma once

struct Vec2
{
	static Vec2 Zero();
	static Vec2 UnitX();
	static Vec2 UnitY();

	Vec2(float x, float y);
	Vec2() = default;
	Vec2(const Vec2& other) = default;

	float squaredLength() const;
	float length() const;
	Vec2 normalize() const;
	float dot(const Vec2& other) const;

	float x, y;
};

Vec2 operator-(const Vec2& v);
Vec2 operator+(const Vec2& left, const Vec2& right);
Vec2 operator-(const Vec2& left, const Vec2& right);
Vec2 operator*(const Vec2& left, float right);
Vec2 operator/(const Vec2& left, float right);
