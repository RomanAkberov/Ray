#pragma once
#include <memory>
#include <optional>
#include "ObjectHit.hpp"
#include "../math/Aabb.hpp"

struct RaySegment;
class Shape;
class Material;

class Object
{
public:
	Object(std::unique_ptr<Shape>&& surface, std::shared_ptr<Material> material);
	std::optional<ObjectHit> intersect(const RaySegment& segment) const;
	Aabb getBounds() const;
private:
	std::unique_ptr<Shape> shape;
	std::shared_ptr<Material> material;
};