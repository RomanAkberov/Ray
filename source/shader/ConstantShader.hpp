#pragma once
#include "Shader.hpp"

class ConstantShader : public Shader
{
public:
	explicit ConstantShader(Color color);
	Color getPixel(const ShapePoint& point) const override;
private:
	const Color color;
};
