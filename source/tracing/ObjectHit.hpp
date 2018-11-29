#pragma once
#include <memory>
#include "../material/Material.hpp"
#include "../shape/ShapeHit.hpp"
#include "../Color.hpp"

class Material;
class Random;

struct ObjectHit
{
	ObjectHit(ShapeHit surfaceHit, std::shared_ptr<Material> material);
	float getT() const;
	Color emit() const;
	std::optional<ScatterResult> scatter(const Ray& ray, Random& random) const;
private:
	ShapeHit shapeHit;
	std::shared_ptr<Material> material;
};
