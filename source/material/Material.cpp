#include "material.hpp"

Vec3 reflect(const Vec3& v, const Vec3& n)
{
	return v - n * (n.dot(v) * 2.0f);
}

std::optional<Vec3> refract(const Vec3& v, const Vec3& n, float refractionRatio)
{
	const auto unitV = v.normalize();
	const auto dot = unitV.dot(n);
	const auto discriminant = 1.0f - refractionRatio * refractionRatio * (1.0f - dot * dot);
	if (discriminant > 0.0f)
	{
		return (unitV - n * dot) * refractionRatio - n * std::sqrt(discriminant);
	}
	return std::nullopt;
}

float reflectionProbability(float cosine, float refractionIndex)
{
	auto r0 = (1.0f - refractionIndex) / (1.0f + refractionIndex);
	r0 *= r0;
	return r0 + (1.0f - r0) * std::pow(1 - cosine, 5);
}

ScatterResult::ScatterResult(Color color, Ray ray) :
	color(color), ray(ray)
{}

Color Material::emit(const ShapePoint&) const
{
	return Color::Black();
}
