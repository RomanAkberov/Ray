#pragma once
#include "material.hpp"

class MetallicMaterial : public Material
{
public:
	explicit MetallicMaterial(Color albedo, float f = 0.0f);
	std::optional<ScatterResult> scatter(const Query& query) const override;
private:
	const Color color;
	const float f;
};
