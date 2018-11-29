#pragma once
#include "../Color.hpp"

struct ShapePoint;

class Shader
{
public:
	virtual Color getPixel(const ShapePoint& point) const = 0;
	virtual ~Shader() = default;
};
