#include <vector>
#include "material/DielectricMaterial.hpp"
#include "material/DiffuseMaterial.hpp"
#include "material/IsotropicMaterial.hpp"
#include "material/LightMaterial.hpp"
#include "material/MetallicMaterial.hpp"
#include "math/Vec2.hpp"
#include "math/Vec3.hpp"
#include "shader/ConstantShader.hpp"
#include "shader/FlatShader.hpp"
#include "shader/NoiseShader.hpp"
#include "shape/ConstantMedium.hpp"
#include "shape/Cuboid.hpp"
#include "shape/Rect.hpp"
#include "shape/ShapeList.hpp"
#include "shape/Sphere.hpp"
#include "tracing/RayTracer.hpp"
#include "tracing/Scene.hpp"
#include "tracing/Settings.hpp"
#include "Texture.hpp"

std::shared_ptr<DiffuseMaterial> diffuseColor(Color color)
{
	return std::make_shared<DiffuseMaterial>(std::make_unique<ConstantShader>(color));
}

auto lightColor(Color color)
{
	return std::make_shared<LightMaterial>(std::make_unique<ConstantTexture>(color));
}

Scene cornellBox()
{
	const auto size = 555.0f;
	const auto red = diffuseColor(Color(0.65f, 0.05f, 0.05f));
	const auto white = diffuseColor(Color(0.73f, 0.73f, 0.73f));
	const auto green = diffuseColor(Color(0.12f, 0.45f, 0.15f));
	const auto smoke = std::make_shared<IsotropicMaterial>(std::make_unique<ConstantShader>(Color(0.9f, 0.9f, 0.9f)));
	const auto light = lightColor(Color(15.0f, 15.0f, 15.0f));
	auto objects = std::vector<Object>{};
	objects.emplace_back(std::make_unique<FlipNormals<RectYz>>(Vec2::Zero(), Vec2{size, size}, size), green);
	objects.emplace_back(std::make_unique<RectYz>(Vec2::Zero(), Vec2{size, size}, 0.0f), red);
	objects.emplace_back(std::make_unique<FlipNormals<RectXz>>(Vec2::Zero(), Vec2{size, size}, size), white);
	objects.emplace_back(std::make_unique<RectXz>(Vec2::Zero(), Vec2{size, size}, 0.0f), white);
	objects.emplace_back(std::make_unique<FlipNormals<RectXy>>(Vec2::Zero(), Vec2{size, size}, size), white);
	objects.emplace_back(std::make_unique<Cuboid>(Vec3{130.0f, 0.0f, 65.f}, Vec3{295.0f, 165.0f, 230.0f}), white);
	objects.emplace_back(std::make_unique<ConstantMedium>(0.2f, std::make_unique<Cuboid>(Vec3{265.0f, 0.0f, 295.f}, Vec3{430.0f, 330.0f, 460.0f})), smoke);
	objects.emplace_back(std::make_unique<RectXz>(Vec2{213.0f, 227.0f}, Vec2{343.0f, 332.0f}, size - 1.0f), light);
	return Scene(std::move(objects));
}

Scene theNextWeekCover()
{
	int nb = 20;
	const auto white = diffuseColor(Color{0.73f, 0.73f, 0.73f});
	const auto ground = diffuseColor(Color{0.48f, 0.83f, 0.53f});
	auto random = Random{321};
	auto objects = std::vector<Object>();
	auto list1 = std::vector<std::unique_ptr<Shape>>();
	for (auto i = 0; i < nb; i++)
	{
		for (auto j = 0; j < nb; j++)
		{
			const auto w = 100.0f;
			const auto min = Vec3{-1000.0f + i * w, -1000.0f + j * w, 0.0f};
			const auto max = Vec3{min.x + w, (random.range01() + 0.01f) * 100.0f, min.z + w};
			list1.emplace_back(std::make_unique<Cuboid>(min, max));
		}
	}
	objects.emplace_back(std::make_unique<ShapeList>(std::move(list1)), ground);
	const auto light = lightColor(Color{7.0f, 7.0f, 7.0f});
	objects.emplace_back(std::make_unique<RectXz>(Vec2{123.0f, 147.0f}, Vec2{423.0f, 412.0f}, 554.0f), light);
	const auto center = Vec3{400, 400, 200};
	objects.emplace_back(std::make_unique<Sphere>(Vec3{260.0f, 150.0f, 45.0f}, 50.0f), std::make_shared<DielectricMaterial>(1.5f));
	objects.emplace_back(std::make_unique<Sphere>(Vec3{0.0f, 150.0f, 145.0f}, 50.0f), std::make_shared<MetallicMaterial>(Color{0.8f, 0.8f, 0.9f}, 10.0f));
	objects.emplace_back(std::make_unique<ConstantMedium>(0.2f, std::make_unique<Sphere>(Vec3(360.0f, 150.0f, 145.0f), 70.0f)), diffuseColor(Color{0.2f, 0.4f, 0.9f}));
	objects.emplace_back(std::make_unique<Sphere>(Vec3{220.0f, 280.0f, 300.0f}, 80.0f), std::make_shared<DiffuseMaterial>(std::make_unique<NoiseShader>(0.1f)));
	auto list2 = std::vector<std::unique_ptr<Shape>>();
	for (auto j = 0; j < 1000; j++)
	{
		list2.emplace_back(std::make_unique<Sphere>(Vec3{165.0f * random.range01(), 165.0f * random.range01(), 165.0f * random.range01()}, 10.0f));
	}
	objects.emplace_back(std::make_unique<Translate<ShapeList>>(Vec3(-100.0f, 270.0f, 395.0f), std::move(list2)), white);
	return Scene(std::move(objects));
}

int main()
{
	const auto scene = theNextWeekCover();
	const auto settings = Settings
	{
		"the-next-week-cover.ppm",
		640u, 480u,
		14, 50, 50
	};
	const auto aspect = static_cast<float>(settings.frameWidth) / static_cast<float>(settings.frameHeight);
	const auto camera = Camera(Vec3(478.0f, 278.0f, -600.0f), Vec3(278.0f, 278.0f, 0.0f), Vec3::UnitY(), 40.0f, aspect, 0.0f, 10.0f);
	const auto rayTracer = RayTracer(camera, std::make_unique<ConstantTexture>(Color::Black()));
	rayTracer.render(scene, settings);
}
