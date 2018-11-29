#pragma once
#include "Shape.hpp"

class RectXy : public Shape
{
public:
	RectXy(Vec2 min, Vec2 max, float k);
	std::optional<ShapeHit> intersect(const RaySegment& segment) const override;
	Aabb getBounds() const override;
private:
	Vec2 min;
	Vec2 max;
	float k;
};

class RectXz : public Shape
{
public:
	RectXz(Vec2 min, Vec2 max, float k);
	std::optional<ShapeHit> intersect(const RaySegment& segment) const override;
	Aabb getBounds() const override;
private:
	const Vec2 min;
	const Vec2 max;
	const float k;
};

class RectYz : public Shape
{
public:
	RectYz(Vec2 min, Vec2 max, float k);
	std::optional<ShapeHit> intersect(const RaySegment& segment) const override;
	Aabb getBounds() const override;
private:
	const Vec2 min;
	const Vec2 max;
	const float k;
};
