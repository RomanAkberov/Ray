#include "NoiseShader.hpp"
#include "../shape/ShapePoint.hpp"

NoiseShader::NoiseShader(float scale) :
	scale(scale)
{}

Color NoiseShader::getPixel(const ShapePoint& point) const
{
	return Color::White() * 0.5f * (perlin.evaluate(point.position * scale) + 1.0f);
}
