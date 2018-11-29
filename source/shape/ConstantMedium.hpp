#pragma once
#include "Shape.hpp"

class ConstantMedium : public Shape
{
public:
	ConstantMedium(float density, std::unique_ptr<Shape>&& boundary);
	std::optional<ShapeHit> intersect(const RaySegment& segment) const override;
	Aabb getBounds() const override;
private:
	const float density;
	const std::unique_ptr<Shape> boundary;
	mutable Random random;
};
