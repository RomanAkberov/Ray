#include "Ray.hpp"

Ray::Ray(Vec3 origin, Vec3 direction) :
	origin{origin}, direction{direction}
{}

Vec3 Ray::at(float t) const
{
	return origin + direction * t;
}

RaySegment::RaySegment(Ray ray, float tMin, float tMax) :
	ray{ray}, tMin{tMin}, tMax{tMax}
{}

bool RaySegment::contains(float t) const
{
	return t >= tMin && t <= tMax;
}

RaySegment RaySegment::translate(Vec3 offset) const
{
	return RaySegment(Ray(ray.origin + offset, ray.direction), tMin, tMax);
}
