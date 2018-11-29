#pragma once
#include "../math/ray.hpp"
#include "../shape/Shape.hpp"
#include "../random/Random.hpp"

struct Query
{
    const Ray& ray;
    const ShapePoint& point;
    Random& random;
};
