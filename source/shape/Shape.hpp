#pragma once
#include <array>
#include <memory>
#include <optional>
#include <vector>
#include "ShapeHit.hpp"
#include "../math/Vec2.hpp"
#include "../math/Aabb.hpp"
#include "../random/Random.hpp"

struct RaySegment;

class Shape
{
public:
	virtual std::optional<ShapeHit> intersect(const RaySegment& segment) const = 0;
	virtual Aabb getBounds() const = 0;
	virtual ~Shape() {}
};

template<typename ShapeT>
class FlipNormals : public Shape
{
public:
	template<typename... Args>
	FlipNormals(Args&&... args) : 
		shape(std::forward<Args>(args)...)
	{}

	std::optional<ShapeHit> intersect(const RaySegment& segment) const override
	{
		if (auto hit = shape.intersect(segment))
		{
			hit->point.normal = -hit->point.normal;
			return hit;
		}
		return std::nullopt;
	}

	Aabb getBounds() const override
	{
		return shape.getBounds();
	}
private:
	const ShapeT shape;
};

template<typename ShapeT>
class Translate : public Shape
{
public:
	template<typename... Args>
	Translate(Vec3 offset, Args&&... args) : 
		offset(offset),
		shape(std::forward<Args>(args)...)
	{}

	std::optional<ShapeHit> intersect(const RaySegment& segment) const override
	{
		const auto translated = segment.translate(-offset);
		if (auto hit = shape.intersect(translated))
		{
			hit->point.position += offset;
			return hit;
		}
		return std::nullopt;
	}

	Aabb getBounds() const override
	{
		return shape.getBounds().translate(offset);
	}
private:
	const Vec3 offset;
	const ShapeT shape;
};

template<typename Shapes>
std::optional<ShapeHit> intersectMany(Shapes& shapes, const RaySegment& segment)
{
	auto result = std::optional<ShapeHit>{};
	auto tClosest = std::numeric_limits<float>::max();
	for (const auto& shape : shapes)
	{
		if (const auto hit = shape->intersect(segment))
		{
			if (hit->t < tClosest)
			{
				result = hit;
				tClosest = hit->t;
			}
		}
	}
	return result;
}
