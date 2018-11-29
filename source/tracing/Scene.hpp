#pragma once
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include "../math/Aabb.hpp"
#include "Object.hpp"
#include "ObjectHit.hpp"

struct RaySegment;
class Material;
class Shape;
class BvhNode;

class Scene
{
public:
	Scene(std::vector<Object> objects);
	~Scene();
	std::optional<ObjectHit> intersect(const Ray& ray) const;
private:
	const std::unique_ptr<BvhNode> root;
	const std::vector<Object> objects;
};
