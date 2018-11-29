#include "random.hpp"

Random::Random(Random::Seed seed) :
	state{seed}
{}

Vec3 Random::onUnitSphere()
{
	while (true)
	{
		const auto v = Vec2{range(-1.0f, 1.0f), range(-1.0f, 1.0f)};
		const auto squaredLength = v.squaredLength();
		if (squaredLength < 1.0f)
		{
			const auto scale = 2.0f * std::sqrt(1.0f - squaredLength);
			const auto z = 1.0f - 2.0f * squaredLength;
			return Vec3{ v.x * scale, v.y * scale, z };
		}
	}
}

Vec3 Random::inUnitSphere()
{
	while (true)
	{
		const auto v = Vec3{range(-1.0f, 1.0f), range(-1.0f, 1.0f), range(-1.0f, 1.0f)};
		if (v.squaredLength() < 1.0f)
		{
			return v;
		}
	}
}

Vec2 Random::inUnitCircle()
{
	while (true)
	{
		const auto v = Vec2{range(-1.0f, 1.0f), range(-1.0f, 1.0f)};
		if (v.squaredLength() < 1.0f)
		{
			return v;
		}
	}
}

float Random::range01()
{
	xorShift();
	return static_cast<float>(state & 0xFFFFFF) / 16777216.0f;
}

float Random::range(float min, float max)
{
	return min + range01() * (max - min);
}

void Random::xorShift()
{
	state ^= state << 13;
	state ^= state >> 17;
	state ^= state << 15;
}
