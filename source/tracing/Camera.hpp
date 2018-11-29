#pragma once
#include "../math/Ray.hpp"
#include "../math/Vec2.hpp"
#include "../math/Vec3.hpp"

class Random;

class Camera
{
public:
	Camera(Vec3 eye, Vec3 target, Vec3 vup, float vfov, float aspect, float aperture, float focusDistance);
	Ray getRay(Vec2 uv, Random& random) const;
private:
	Vec3 eye;
	Vec3 lowerLeftCorner;
	Vec3 right;
	Vec3 up;
	Vec3 u, v;
	float lensRadius;
};
