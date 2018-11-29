#include "ObjectHit.hpp"
#include "../material/Material.hpp"
#include "../material/Query.hpp"

ObjectHit::ObjectHit(ShapeHit shapeHit, std::shared_ptr<Material> material) :
	shapeHit{shapeHit}, 
	material{material}
{}

Color ObjectHit::emit() const
{
	return material->emit(shapeHit.point);
}

std::optional<ScatterResult> ObjectHit::scatter(const Ray& ray, Random& random) const
{
	return material->scatter(Query{ ray, shapeHit.point, random });
}

float ObjectHit::getT() const
{
	return shapeHit.t;
}
