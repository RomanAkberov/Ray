#pragma once
#include <optional>
#include "../Color.hpp"
#include "../math/Ray.hpp"

class Random;
struct ShapePoint;
struct Query;

struct ScatterResult
{
	ScatterResult(Color color, Ray ray);
	const Color color;
	const Ray ray;
};

class Material
{
public:
	virtual std::optional<ScatterResult> scatter(const Query& query) const = 0;
	virtual Color emit(const ShapePoint& point) const;
	virtual ~Material() = default;
};

Vec3 reflect(const Vec3& v, const Vec3& n);
std::optional<Vec3> refract(const Vec3& v, const Vec3& n, float refractionRatio);
float reflectionProbability(float cosine, float refractionIndex);
