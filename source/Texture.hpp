#pragma once
#include "Color.hpp"
#include "math/Vec2.hpp"

class Texture
{
public:
	virtual Color getPixel(Vec2 uv) const = 0;
	virtual ~Texture() = default;
};

class ConstantTexture : public Texture
{
public:
	ConstantTexture(Color color);
	Color getPixel(Vec2 uv) const override;
private:
	const Color color;
};