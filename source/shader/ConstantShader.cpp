#include "ConstantShader.hpp"

ConstantShader::ConstantShader(Color color) :
    color{color}
{}

Color ConstantShader::getPixel(const ShapePoint&) const
{
	return color;
}
