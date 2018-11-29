#pragma once
#include "material.hpp"

class DielectricMaterial : public Material
{
public:
	explicit DielectricMaterial(float refractionIndex);
	std::optional<ScatterResult> scatter(const Query& query) const override;
private:
	const float refractionIndex;
};
