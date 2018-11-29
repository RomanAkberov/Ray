#include "MetallicMaterial.hpp"
#include "../math/ray.hpp"
#include "../random/Random.hpp"
#include "Query.hpp"

MetallicMaterial::MetallicMaterial(Color color, float f) :
	color{color}, f{f}
{}

std::optional<ScatterResult> MetallicMaterial::scatter(const Query& query) const
{
	const auto reflection = reflect(query.ray.direction.normalize(), query.point.normal);
	const auto outRay = Ray{query.point.position, reflection + query.random.inUnitSphere() * f};
	if (outRay.direction.dot(query.point.normal) > 0.0f)
	{
		return ScatterResult{color, outRay};
	}
	return std::nullopt;
}
