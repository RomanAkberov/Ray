#include "Texture.hpp"

ConstantTexture::ConstantTexture(Color color) :
	color{color}
{}

Color ConstantTexture::getPixel(Vec2) const
{
	return color;
}
