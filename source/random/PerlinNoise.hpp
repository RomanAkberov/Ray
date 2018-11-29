#pragma once
#include "../math/Vec3.hpp"
#include "Random.hpp"

class PerlinNoise
{
public:
	PerlinNoise();
	float evaluate(const Vec3& v) const;
private:
	PerlinNoise(Random random);
	const std::vector<std::uint8_t> xPerm;
	const std::vector<std::uint8_t> yPerm;
	const std::vector<std::uint8_t> zPerm;
	const std::vector<Vec3> gradients;
};
