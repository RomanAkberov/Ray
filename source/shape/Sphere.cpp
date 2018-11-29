#include "Sphere.hpp"

constexpr float Pi = 3.14159265358979323846f;

ShapeHit hit(const Sphere& sphere, const Ray& ray, float t)
{
	const auto position = ray.at(t);
	const auto phi = std::atan2(position.z, position.x);
	const auto theta = std::asin(position.y);
	const auto texCoord = Vec2(0.5f - phi / (2.0f * Pi), 0.5f + theta / Pi);
	return ShapeHit
	{
		ShapePoint
		{
			position,
			(position - sphere.getCenter()) / sphere.getRadius(),
			texCoord,
		},
		t
	};
}

Sphere::Sphere(Vec3 center, float radius) :
	center{center}, radius{radius}
{}

std::optional<ShapeHit> Sphere::intersect(const RaySegment& segment) const
{
	const auto oc = segment.ray.origin - center;
	const auto a = segment.ray.direction.dot(segment.ray.direction);
	const auto b = oc.dot(segment.ray.direction);
	const auto c = oc.dot(oc) - radius * radius;
	const auto discriminant = b * b - a * c;
	if (discriminant > 0.0f)
	{
		const auto sqrtD = std::sqrt(discriminant);
		const auto t1 = (-b - sqrtD) / a;
		if (t1 > segment.tMin && t1 < segment.tMax)
		{
			return hit(*this, segment.ray, t1);
		}
		const auto t2 = (-b + sqrtD) / a;
		if (segment.contains(t2))
		{
			return hit(*this, segment.ray, t2);
		}
	}
	return std::nullopt;
}

Aabb Sphere::getBounds() const
{
	return Aabb(
		center - Vec3(radius, radius, radius),
		center + Vec3(radius, radius, radius));
}

Vec3 Sphere::getCenter() const
{
	return center;
}

float Sphere::getRadius() const
{
	return radius;
}
