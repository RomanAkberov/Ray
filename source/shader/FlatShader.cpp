#include "FlatShader.hpp"
#include "../shape/ShapePoint.hpp"
#include "../Texture.hpp"

FlatShader::FlatShader(std::unique_ptr<Texture>&& texture):
	texture{std::move(texture)}
{}

FlatShader::~FlatShader() = default;

Color FlatShader::getPixel(const ShapePoint& point) const
{
    return texture->getPixel(point.uv);
}
