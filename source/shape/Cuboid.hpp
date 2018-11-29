#pragma once
#include "Shape.hpp"

class Cuboid : public Shape
{
public:
	Cuboid(Vec3 min, Vec3 max);
	std::optional<ShapeHit> intersect(const RaySegment& segment) const override;
	Aabb getBounds() const override;
private:
	const Aabb bounds;
	const std::array<std::unique_ptr<Shape>, 6> sides;
};
