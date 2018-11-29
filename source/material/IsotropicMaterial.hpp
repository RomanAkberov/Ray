#pragma once
#include <memory>
#include "material.hpp"

class Shader;

class IsotropicMaterial : public Material
{
public:
	IsotropicMaterial(std::unique_ptr<Shader>&& shader);
	~IsotropicMaterial();
	std::optional<ScatterResult> scatter(const Query& query) const override;
private:
	const std::unique_ptr<Shader> shader;
};
