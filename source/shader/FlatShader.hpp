#pragma once
#include <memory>
#include "Shader.hpp"

class Texture;

class FlatShader : public Shader
{
public: 
	FlatShader(std::unique_ptr<Texture>&& texture);
	~FlatShader();
	Color getPixel(const ShapePoint& point) const override;
private:
	const std::unique_ptr<Texture> texture;
};
