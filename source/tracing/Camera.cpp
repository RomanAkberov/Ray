#include "Camera.hpp"
#include "../random/Random.hpp"

constexpr float Pi = 3.14159265358979323846f;

Camera::Camera(Vec3 eye, Vec3 target, Vec3 vup, float vfov, float aspect, float aperture, float focusDistance) :
	eye{eye},
	lensRadius{aperture / 2}
{
	const auto theta = (Pi / 180) * vfov;
	const auto w = (eye - target).normalize();
	u = vup.cross(w).normalize();
	v = w.cross(u);
	const auto halfHeight = std::tan(theta / 2) * focusDistance;
	const auto halfWidth = aspect * halfHeight;
	lowerLeftCorner = eye - u * halfWidth - v * halfHeight - w * focusDistance;
	right = u * (2 * halfWidth);
	up = v * (2 * halfHeight);
}

Ray Camera::getRay(Vec2 uv, Random& random) const
{
	const auto rd = random.inUnitCircle() * lensRadius;
	const auto offset = u * rd.x + v * rd.y;
	return Ray(eye + offset, lowerLeftCorner + right * uv.x + up * uv.y - eye - offset);
}
