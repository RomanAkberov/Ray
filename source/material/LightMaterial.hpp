#pragma once
#include <memory>
#include "Material.hpp"

class Texture;

class LightMaterial : public Material
{
public:
	LightMaterial(std::unique_ptr<Texture>&& texture);
	~LightMaterial();
	Color emit(const ShapePoint& point) const override;
	std::optional<ScatterResult> scatter(const Query& query) const override;
private:
	const std::unique_ptr<Texture> texture;
};
