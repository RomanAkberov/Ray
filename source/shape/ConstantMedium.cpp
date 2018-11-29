#include "ConstantMedium.hpp"

ConstantMedium::ConstantMedium(float density, std::unique_ptr<Shape>&& boundary): 
	density{density},
	boundary{std::move(boundary)},
	random{321}
{}

std::optional<ShapeHit> ConstantMedium::intersect(const RaySegment& segment) const
{
	const auto segment1 = RaySegment{segment.ray, std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max()};
	if (auto hit1 = boundary->intersect(segment1))
	{
		const auto segment2 = RaySegment{segment.ray, hit1->t + 0.0001f, std::numeric_limits<float>::max()};
		if (auto hit2 = boundary->intersect(segment2))
		{
			if (hit1->t < segment.tMin)
			{
				hit1->t = segment.tMin;
			}
			if (hit2->t > segment.tMax)
			{
				hit2->t = segment.tMax;
			}
			if (hit1->t >= hit2->t)
			{
				return std::nullopt;
			}
			if (hit1->t < 0.0f)
			{
				hit1->t = 0.0f;
			}
			const auto directionLength = segment.ray.direction.length();
			const auto distInside = (hit2->t - hit1->t) * directionLength;
			const auto hitDist = -(1.0f / density) * std::log(random.range01());
			if (hitDist < distInside)
			{
				const auto t = hit1->t + hitDist / directionLength;
				return ShapeHit
				{
					ShapePoint
					{
						segment.ray.at(t),
						Vec3::UnitX(),
						Vec2::Zero(),
					},
					t
				};
			}
		}
	}
	return std::nullopt;
}

Aabb ConstantMedium::getBounds() const
{
    return boundary->getBounds();
}
