#include "Cuboid.hpp"
#include "Rect.hpp"

Cuboid::Cuboid(Vec3 min, Vec3 max) :
	bounds{min, max},
	sides
	{
		std::make_unique<RectXy>(Vec2{min.x, min.y}, Vec2{max.x, max.y}, max.z),
		std::make_unique<FlipNormals<RectXy>>(Vec2{min.x, min.y}, Vec2{max.x, max.y}, min.z),
		std::make_unique<RectXz>(Vec2{min.x, min.z}, Vec2{max.x, max.z}, max.y),
		std::make_unique<FlipNormals<RectXz>>(Vec2{min.x, min.y}, Vec2{max.x, max.y}, min.y),
		std::make_unique<RectYz>(Vec2{min.y, min.z}, Vec2{max.y, max.z}, max.x),
		std::make_unique<FlipNormals<RectYz>>(Vec2{min.y, min.z}, Vec2{max.y, max.z}, min.x),
	}
{}

std::optional<ShapeHit> Cuboid::intersect(const RaySegment& segment) const
{
	return intersectMany(sides, segment);
}

Aabb Cuboid::getBounds() const
{
	return bounds;
}
