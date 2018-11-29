#include "DiffuseMaterial.hpp"
#include "../shader/Shader.hpp"
#include "Query.hpp"

DiffuseMaterial::DiffuseMaterial(std::unique_ptr<Shader>&& shader):
	shader{std::move(shader)}
{}

DiffuseMaterial::~DiffuseMaterial() = default;

std::optional<ScatterResult> DiffuseMaterial::scatter(const Query& query) const
{
    return ScatterResult{shader->getPixel(query.point), Ray{query.point.position, query.point.normal + query.random.onUnitSphere()}};
}
