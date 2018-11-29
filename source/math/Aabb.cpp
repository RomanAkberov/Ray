#include "Aabb.hpp"
#include <utility>

bool intersectSlab(float d, float o,
	float min, float max,
	float tMin, float tMax)
{
	const auto invD = 1.0f / d;
	auto t0 = (min - o) * invD;
	auto t1 = (max - o) * invD;
	if (invD < 0.0f)
	{
		std::swap(t0, t1);
	}
	tMin = t0 > tMin ? t0 : tMin;
	tMax = t1 < tMax ? t1 : tMax;
	return tMin < tMax;
}

Aabb::Aabb(Vec3 min, Vec3 max) :
	min{min}, max{max}
{}

Vec3 Aabb::getCentroid() const
{
	return (min + max) * 0.5f;
}

Vec3 Aabb::getDiagonal() const
{
	return max - min;
}

Axis Aabb::getMaxAxis() const
{
	const auto diagonal = getDiagonal();
	if (diagonal.x > diagonal.y && diagonal.x > diagonal.z)
	{
		return Axis::X;
	}
	if (diagonal.y > diagonal.z)
	{
		return Axis::Y;
	}
	return Axis::Z;
}

bool Aabb::intersect(const RaySegment& segment) const
{
	return intersectSlab(segment.ray.direction.x, segment.ray.origin.x, min.x, max.x, segment.tMin, segment.tMax) &&
		intersectSlab(segment.ray.direction.y, segment.ray.origin.y, min.y, max.y, segment.tMin, segment.tMax) &&
		intersectSlab(segment.ray.direction.z, segment.ray.origin.z, min.z, max.z, segment.tMin, segment.tMax);
}

Aabb Aabb::translate(const Vec3& offset) const
{
	return Aabb{min + offset, max + offset};
}

void Aabb::extend(const Aabb& other) {
	min = min.min(other.min);
	max = max.max(other.max);
}
