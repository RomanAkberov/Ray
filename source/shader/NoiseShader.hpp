#pragma once
#include "Shader.hpp"
#include "../random/PerlinNoise.hpp"

class NoiseShader : public Shader
{
public:
	explicit NoiseShader(float scale);
	Color getPixel(const ShapePoint& point) const override;
private:
	const float scale;
	const PerlinNoise perlin;
};
