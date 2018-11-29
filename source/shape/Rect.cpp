#include "Rect.hpp"

constexpr float Width = 0.0001f;

RectXy::RectXy(Vec2 min, Vec2 max, float k) :
	min(min), max(max), k(k)
{}

std::optional<ShapeHit> RectXy::intersect(const RaySegment& segment) const
{
	const auto t = (k - segment.ray.origin.z) / segment.ray.direction.z;
	if (!segment.contains(t))
	{
		return std::nullopt;
	}
	const auto point = segment.ray.at(t);
	if (point.x < min.x || point.x > max.x || point.y < min.y || point.y > max.y)
	{
		return std::nullopt;
	}
	return ShapeHit
	{
		ShapePoint
		{
			point,
			Vec3::UnitZ(),
			Vec2((point.x - min.x) / (max.x - min.x), (point.y - min.y) / (max.y - min.y)),
		},
		t
	};
}

Aabb RectXy::getBounds() const
{
	return Aabb(
		Vec3(min.x, min.y, k - Width),
		Vec3(max.x, max.y, k + Width));
}

RectXz::RectXz(Vec2 min, Vec2 max, float k) :
	min(min), max(max), k(k)
{}

std::optional<ShapeHit> RectXz::intersect(const RaySegment& segment) const
{
	const auto t = (k - segment.ray.origin.y) / segment.ray.direction.y;
	if (!segment.contains(t))
	{
		return std::nullopt;
	}
	const auto point = segment.ray.at(t);
	if (point.x < min.x || point.x > max.x || point.z < min.y || point.z > max.y)
	{
		return std::nullopt;
	}
	return ShapeHit
	{
		point,
		Vec3::UnitY(),
		Vec2((point.x - min.x) / (max.x - min.x), (point.z - min.y) / (max.y - min.y)),
		t
	};
}

Aabb RectXz::getBounds() const
{
	return Aabb(
		Vec3(min.x, k - Width, min.y),
		Vec3(max.x, k + Width, max.y));
}

RectYz::RectYz(Vec2 min, Vec2 max, float k) :
	min(min), max(max), k(k)
{}

std::optional<ShapeHit> RectYz::intersect(const RaySegment& segment) const
{
	const auto t = (k - segment.ray.origin.x) / segment.ray.direction.x;
	if (!segment.contains(t))
	{
		return std::nullopt;
	}
	const auto point = segment.ray.at(t);
	if (point.y < min.x || point.y > max.x || point.z < min.y || point.z > max.y)
	{
		return std::nullopt;
	}
	return ShapeHit
	{
		point,
		Vec3::UnitX(),
		Vec2((point.y - min.x) / (max.x - min.x), (point.z - min.y) / (max.y - min.y)),
		t
	};
}

Aabb RectYz::getBounds() const
{
	return Aabb(
		Vec3(k - Width, min.x, min.y),
		Vec3(k + Width, max.x, max.y));
}