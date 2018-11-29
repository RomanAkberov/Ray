#include "IsotropicMaterial.hpp"
#include "Query.hpp"
#include "../shader/shader.hpp"

IsotropicMaterial::IsotropicMaterial(std::unique_ptr<Shader>&& shader):
	shader{std::move(shader)}
{}

IsotropicMaterial::~IsotropicMaterial() = default;

std::optional<ScatterResult> IsotropicMaterial::scatter(const Query & query) const
{
	return ScatterResult{shader->getPixel(query.point), Ray{query.point.position, query.random.onUnitSphere()}};
}
