#pragma once

enum class Axis
{
	X,
	Y,
	Z
};

struct Vec3
{
	static Vec3 Zero();
	static Vec3 UnitX();
	static Vec3 UnitY();
	static Vec3 UnitZ();

	Vec3(float x, float y, float z);
	Vec3() = default;
	Vec3(const Vec3& other) = default;

	float operator[](Axis axis) const;
	Vec3& operator+=(const Vec3& other);
	Vec3& operator-=(const Vec3& other);
	Vec3& operator*=(float other);
	Vec3& operator/=(float other);

	float squaredLength() const;
	float length() const;
	Vec3 normalize() const;
	float dot(const Vec3& other) const;
	Vec3 cross(const Vec3& other) const;

	Vec3 min(const Vec3& other) const;
	Vec3 max(const Vec3& other) const;

	float x, y, z;
};

Vec3 operator-(const Vec3& v);
Vec3 operator+(const Vec3& left, const Vec3& right);
Vec3 operator-(const Vec3& left, const Vec3& right);
Vec3 operator*(const Vec3& left, float right);
Vec3 operator/(const Vec3& left, float right);
