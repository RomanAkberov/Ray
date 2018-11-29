#pragma once
#include <cstdint>
#include <string>

struct Settings
{	
	std::string imagePath;
	std::uint32_t frameWidth;
	std::uint32_t frameHeight;
	std::uint32_t numThreads;
	std::uint32_t maxDepth;
	std::uint32_t raysPerPixel;
};
