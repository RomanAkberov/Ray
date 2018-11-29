#include "DielectricMaterial.hpp"
#include <tuple>
#include "../random/Random.hpp"
#include "../shape/Shape.hpp"
#include "Query.hpp"

DielectricMaterial::DielectricMaterial(float refractionIndex) :
	refractionIndex{refractionIndex}
{}

std::optional<ScatterResult> DielectricMaterial::scatter(const Query& query) const
{
	const auto dot = query.ray.direction.normalize().dot(query.point.normal);
	auto [outNormal, refractionRatio, cosine] = (dot > 0.0f) ? 
		std::make_tuple(-query.point.normal, refractionIndex, refractionIndex * dot) :
		std::make_tuple(query.point.normal, 1.0f / refractionIndex, -dot);
	if (const auto refracted = refract(query.ray.direction, outNormal, refractionRatio))
	{
		if (query.random.range01() >= reflectionProbability(cosine, refractionIndex))
		{
			return ScatterResult{Color::White(), Ray{query.point.position, *refracted}};
		}
	}
	return ScatterResult{Color::White(), Ray{query.point.position, reflect(query.ray.direction, query.point.normal)}};
}
