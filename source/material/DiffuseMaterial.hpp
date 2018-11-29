#pragma once
#include <memory>
#include "Material.hpp"

class Shader;

class DiffuseMaterial : public Material
{
public:
	DiffuseMaterial(std::unique_ptr<Shader>&& shader);
	~DiffuseMaterial();
	std::optional<ScatterResult> scatter(const Query& query) const override;
private:
	const std::unique_ptr<Shader> shader;
};
