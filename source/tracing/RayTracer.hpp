#pragma once
#include <memory>
#include "Camera.hpp"
#include "Scene.hpp"

class Texture;
struct Settings;

class RayTracer
{
public:
	RayTracer(Camera camera, std::unique_ptr<Texture>&& background);
	~RayTracer();
	void render(const Scene& scene, const Settings& settings) const;
private:
	Color trace(const Scene& scene, const Ray& ray, Random& random, std::uint32_t depth) const;
	const Camera camera;
	const std::unique_ptr<Texture> background;
};
