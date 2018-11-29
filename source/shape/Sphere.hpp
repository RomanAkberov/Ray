#pragma once
#include "Shape.hpp"

class Sphere : public Shape
{
public:
	Sphere(Vec3 center, float radius);
	std::optional<ShapeHit> intersect(const RaySegment& segment) const override;
	Aabb getBounds() const override;
    Vec3 getCenter() const;
    float getRadius() const;
private:
	const Vec3 center;
	const float radius;
};
