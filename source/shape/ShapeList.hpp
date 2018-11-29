#pragma once
#include "Shape.hpp"

class ShapeList : public Shape
{
public:
	ShapeList(std::vector<std::unique_ptr<Shape>>&& children);
	std::optional<ShapeHit> intersect(const RaySegment& segment) const override;
	Aabb getBounds() const override;
private:
	Aabb bounds;
	const std::vector<std::unique_ptr<Shape>> children;
};
