#include "RayTracer.hpp"
#include <algorithm>
#include <cmath>
#include <thread>
#include "Settings.hpp"
#include "../Texture.hpp"
#include "../random/Random.hpp"

constexpr float Pi = 3.14159265358979323846f;

uint32_t linearToSrgb(float x)
{
	x = std::max(x, 0.0f);
	x = std::max(1.055f * std::pow(x, 0.416666667f) - 0.055f, 0.0f);
	return std::min(static_cast<uint32_t>(x * 255.9f), 255u);
}

bool savePpm(const std::vector<Color>& pixels, uint32_t width, uint32_t height, const char* path)
{
	FILE* file;
	if (fopen_s(&file, path, "w"))
	{
		return false;
	}
	fprintf(file, "P3\n%d %d\n255\n", width, height);
	for (auto j = 0u; j < height; j++)
	{
		for (auto i = 0u; i < width; i++)
		{
			const auto pixel = pixels[((height - j - 1) * width + i)];
			const auto r = linearToSrgb(pixel.r);
			const auto g = linearToSrgb(pixel.g);
			const auto b = linearToSrgb(pixel.b);
			fprintf(file, "%d %d %d\n", r, g, b);
		}
	}
	return true;
}

RayTracer::RayTracer(Camera camera, std::unique_ptr<Texture>&& background) :
	camera(camera),
	background(std::move(background))
{}

RayTracer::~RayTracer() = default;

void RayTracer::render(const Scene& scene, const Settings& settings) const
{
	auto pixels = std::vector<Color>(settings.frameWidth * settings.frameHeight);
	const auto rowsPerThread = settings.frameWidth / settings.numThreads;
	const auto rem = settings.frameWidth % settings.numThreads;
	auto rowStart = 0u;
	auto threads = std::vector<std::thread>();
	for (auto threadIndex = 0u; threadIndex < settings.numThreads; threadIndex++)
	{
		const auto rowEnd = rowStart + rowsPerThread + (threadIndex < rem);
		threads.emplace_back([&, rowStart, rowEnd, threadIndex]()
		{
			auto random = Random(threadIndex + 1);
			for (auto i = rowStart; i < rowEnd; i++) {
				for (auto j = 0u; j < settings.frameHeight; j++)
				{
					auto pixel = Color::Black();
					for (auto r = 0u; r < settings.raysPerPixel; r++)
					{
						const auto uv = Vec2(
							(i + random.range01()) / settings.frameWidth,
							(j + random.range01()) / settings.frameHeight
						);
						const auto ray = camera.getRay(uv, random);
						pixel += trace(scene, ray, random, settings.maxDepth);
					}
					pixel /= static_cast<float>(settings.raysPerPixel);
					pixels[j * settings.frameWidth + i] = pixel;
				}
			}
		});
		rowStart = rowEnd;
	}
	for (auto& thread : threads)
	{
		thread.join();
	}
	savePpm(pixels, settings.frameWidth, settings.frameHeight, settings.imagePath.c_str());
}

Color RayTracer::trace(const Scene& scene, const Ray& ray, Random& random, uint32_t depth) const
{
	if (const auto hit = scene.intersect(ray))
	{
		auto finalColor = hit->emit();
		if (depth != 0)
		{
			if (const auto result = hit->scatter(ray, random))
			{
				finalColor += result->color * trace(scene, result->ray, random, depth - 1);
			}
		}
		return finalColor;
	}
	const auto v = 0.5f * (ray.direction.normalize().y + 1.0f);
	return background->getPixel(Vec2(0.0, v));
}
