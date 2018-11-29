#include "Object.hpp"
#include "../material/Material.hpp"
#include "../shape/Shape.hpp"

Object::Object(std::unique_ptr<Shape>&& shape, std::shared_ptr<Material> material) :
	shape{std::move(shape)},
	material{material}
{}

std::optional<ObjectHit> Object::intersect(const RaySegment& segment) const
{
	if (const auto hit = shape->intersect(segment))
	{
		return ObjectHit{*hit, material};
	}
	return std::nullopt;
}

Aabb Object::getBounds() const
{
	return shape->getBounds();
}
