#include "PerlinNoise.hpp"

constexpr auto PermutationSize = 256;
constexpr auto Mask = 255;

float hermiteCubic(float x)
{
	return x * x * (3.0f - 2.0f * x);
}

Vec3 hermiteCubic(const Vec3& p)
{
	return {hermiteCubic(p.x), hermiteCubic(p.y), hermiteCubic(p.z)};
}

std::vector<uint8_t> generatePermutation(Random& random)
{
	auto permutation = std::vector<uint8_t>(PermutationSize);
	for (auto i = 0; i < PermutationSize; i++)
	{
		permutation[i] = static_cast<uint8_t>(i);
	}
	for (auto i = PermutationSize - 1; i > 0; i--)
	{
		auto j = static_cast<int>(random.range01() * PermutationSize);
		std::swap(permutation[i], permutation[j]);
	}
	return permutation;
}

std::vector<Vec3> generateGradients(Random& random)
{
	auto gradients = std::vector<Vec3>(PermutationSize);
	for (auto& g : gradients)
	{
		g = random.onUnitSphere();
	}
	return gradients;
}

PerlinNoise::PerlinNoise() :
	PerlinNoise{Random{123}}
{}

PerlinNoise::PerlinNoise(Random random) :
	xPerm{generatePermutation(random)},
	yPerm{generatePermutation(random)},
	zPerm{generatePermutation(random)},
	gradients{generateGradients(random)}
{}

float PerlinNoise::evaluate(const Vec3& p) const
{
	const auto floorP = Vec3(std::floor(p.x), std::floor(p.y), std::floor(p.z));
	const auto fracP = p - floorP;
	const auto hermiteP = hermiteCubic(fracP);
	const auto i = static_cast<int>(floorP.x);
	const auto j = static_cast<int>(floorP.y);
	const auto k = static_cast<int>(floorP.z);
	auto result = 0.0f;
	for (auto di = 0; di < 2; di++)
	{
		for (auto dj = 0; dj < 2; dj++)
		{
			for (auto dk = 0; dk < 2; dk++)
			{
				const auto gridP = Vec3
				{
					static_cast<float>(di),
					static_cast<float>(dj),
					static_cast<float>(dk),
				};
				const auto gradient = gradients[xPerm[(i + di) & Mask] ^ yPerm[(j + dj) & Mask] ^ zPerm[(k + dk) & Mask]];
				result += gradient.dot(fracP - gridP) *
					(gridP.x * hermiteP.x + (1.0f - gridP.x) * (1.0f - hermiteP.x)) *
					(gridP.y * hermiteP.y + (1.0f - gridP.y) * (1.0f - hermiteP.y)) *
					(gridP.z * hermiteP.z + (1.0f - gridP.z) * (1.0f - hermiteP.z));
			}
		}
	}
	return result;
}