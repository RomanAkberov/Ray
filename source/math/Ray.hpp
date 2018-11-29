#pragma once
#include "Vec3.hpp"

struct Ray
{
	Ray(Vec3 origin, Vec3 direction);
	Vec3 at(float t) const;

	Vec3 origin;
	Vec3 direction;
};

struct RaySegment
{
	RaySegment(Ray ray, float tMin, float tMax);
	bool contains(float t) const;
	RaySegment translate(Vec3 offset) const;

	Ray ray;
	float tMin;
	float tMax;
};
