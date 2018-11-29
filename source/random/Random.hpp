#pragma once
#include <cstdint>
#include <vector>
#include "../math/Vec2.hpp"
#include "../math/Vec3.hpp"

class Random
{
public:
	using Seed = std::uint32_t;
	explicit Random(Seed seed);
	Vec3 onUnitSphere();
	Vec3 inUnitSphere();
	Vec2 inUnitCircle();
	float range01();
	float range(float min, float max);
private:
	void xorShift();
	Seed state;
};

