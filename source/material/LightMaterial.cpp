#include "LightMaterial.hpp"
#include "../shape/Shape.hpp"
#include "../Texture.hpp"

LightMaterial::LightMaterial(std::unique_ptr<Texture>&& texture):
	texture{std::move(texture)}
{}

LightMaterial::~LightMaterial() = default;

Color LightMaterial::emit(const ShapePoint& point) const
{
	return texture->getPixel(point.uv);
}

std::optional<ScatterResult> LightMaterial::scatter(const Query&) const
{
	return std::nullopt;
}