#include "Vec3.hpp"
#include <algorithm>
#include <cmath>

Vec3 Vec3::Zero()
{
	return {};
}

Vec3 Vec3::UnitX()
{
	return {1.0f, 0.0f, 0.0f};
}

Vec3 Vec3::UnitY()
{
	return {0.0f, 1.0f, 0.0f};
}

Vec3 Vec3::UnitZ()
{
	return {0.0f, 0.0f, 1.0f};
}

Vec3::Vec3(float x, float y, float z):
	x{x}, y{y}, z{z}
{}

float Vec3::operator[](Axis axis) const
{
	switch (axis)
	{
	case Axis::X:
		return x;
	case Axis::Y:
		return y;
	default:
		return z;
	}
}

Vec3& Vec3::operator+=(const Vec3 & other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vec3& Vec3::operator-=(const Vec3 & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vec3& Vec3::operator*=(float other)
{
	x *= other;
	y *= other;
	z *= other;
	return *this;
}

Vec3 & Vec3::operator/=(float other)
{
	x /= other;
	y /= other;
	z /= other;
	return *this;
}

float Vec3::squaredLength() const
{
	return dot(*this);
}

float Vec3::length() const
{
	return std::sqrt(squaredLength());
}

Vec3 Vec3::normalize() const
{
	return (*this) / length();
}

float Vec3::dot(const Vec3& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::cross(const Vec3& other) const
{
	return
	{
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	};
}

Vec3 Vec3::min(const Vec3& other) const
{
	return {std::min(x, other.x), std::min(y, other.y), std::min(z, other.z)};
}

Vec3 Vec3::max(const Vec3& other) const
{
	return {std::max(x, other.x), std::max(y, other.y), std::max(z, other.z)};
}

Vec3 operator-(const Vec3& v)
{
	return {-v.x, -v.y, -v.z};
}

Vec3 operator+(const Vec3& left, const Vec3 & right)
{
	return {left.x + right.x, left.y + right.y, left.z + right.z};
}

Vec3 operator-(const Vec3& left, const Vec3& right)
{
	return {left.x - right.x, left.y - right.y, left.z - right.z};
}

Vec3 operator*(const Vec3& left, float right)
{
	return {left.x * right, left.y * right, left.z * right};
}

Vec3 operator/(const Vec3& left, float right)
{
	return left * (1.0f / right);
}
