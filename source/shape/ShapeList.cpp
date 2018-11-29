#include "ShapeList.hpp"

ShapeList::ShapeList(std::vector<std::unique_ptr<Shape>>&& children) :
	bounds(children[0]->getBounds()),
	children(std::move(children))
{
	for (auto i = 1u; i < children.size(); i++)
	{
		bounds.extend(children[i]->getBounds());
	}
}

std::optional<ShapeHit> ShapeList::intersect(const RaySegment& segment) const
{
	if (!bounds.intersect(segment))
	{
		//return std::nullopt;
	}
	return intersectMany(children, segment);
}

Aabb ShapeList::getBounds() const
{
	return bounds;
}
