#pragma once
#include "Ray.hpp"
#include "Vec3.hpp"

class Aabb
{
public:
	Aabb(Vec3 min, Vec3 max);
	Aabb() = default;
	Vec3 getCentroid() const;
	Vec3 getDiagonal() const;
	Axis getMaxAxis() const;
	bool intersect(const RaySegment& segment) const;
	Aabb translate(const Vec3& offset) const;
	void extend(const Aabb& other);
private:
	Vec3 min;
	Vec3 max;
};
