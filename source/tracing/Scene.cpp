#include "scene.hpp"
#include <thread>
#include "../material/Query.hpp"

class BvhNode
{
public:
	BvhNode(std::vector<Object>& objects, std::uint32_t startIndex, std::uint32_t endIndex);
	std::optional<ObjectHit> intersect(const std::vector<Object>& objects, const RaySegment& segment) const;
private:
	Aabb bounds;
	std::uint32_t startIndex;
	std::uint32_t endIndex;
	std::unique_ptr<BvhNode> left;
	std::unique_ptr<BvhNode> right;
};

BvhNode::BvhNode(std::vector<Object>& objects, std::uint32_t startIndex, std::uint32_t endIndex):
	bounds(objects[startIndex].getBounds()),
	startIndex(startIndex),
	endIndex(endIndex),
	left(),
	right()
{
	for (auto index = startIndex + 1; index < endIndex; index++)
	{
		bounds.extend(objects[index].getBounds());
	}
	if (endIndex - startIndex > 10)
	{
		const auto axis = bounds.getMaxAxis();
		const auto coord = bounds.getCentroid()[axis];
		const auto midIter = std::partition(&objects[startIndex], &objects[endIndex - 1] + 1, [axis, coord](Object& object)
		{
			return object.getBounds().getCentroid()[axis] < coord;
		});
		const auto midIndex = static_cast<std::uint32_t>(midIter - &objects[0]);
		if (midIndex != startIndex && midIndex != endIndex) {
			left = std::make_unique<BvhNode>(objects, startIndex, midIndex);
			right = std::make_unique<BvhNode>(objects, midIndex, endIndex);
		}
	}
}

std::optional<ObjectHit> BvhNode::intersect(const std::vector<Object>& objects, const RaySegment& segment) const
{
	if (bounds.intersect(segment))
	{
		if (left)
		{
			const auto leftHit = left->intersect(objects, segment);
			const auto rightHit = right->intersect(objects, segment);
			if (leftHit)
			{
				if (rightHit)
				{
					return leftHit->getT() < rightHit->getT() ? leftHit : rightHit;
				}
				return leftHit;
			}
			return rightHit;
		}
		else
		{
			auto result = std::optional<ObjectHit>{};
			auto tClosest = std::numeric_limits<float>::max();
			for (auto index = startIndex; index < endIndex; index++)
			{
				if (const auto hit = objects[index].intersect(segment))
				{
					if (hit->getT() < tClosest)
					{
						result = hit;
						tClosest = hit->getT();
					}
				}
			}
			return result;
		}
	}
	return std::nullopt;
}

Scene::Scene(std::vector<Object> objects) :
	root{std::make_unique<BvhNode>(objects, 0, objects.size())},
	objects{std::move(objects)}
{}

Scene::~Scene() = default;

std::optional<ObjectHit> Scene::intersect(const Ray& ray) const
{
	return root->intersect(objects, RaySegment(ray, 0.0001f, std::numeric_limits<float>::max()));
}
