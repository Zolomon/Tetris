#pragma once

#include "glm/glm.hpp"
#include <chrono>

namespace Settings
{
	namespace Window
	{
		static const glm::vec2 StartPosition(100.0f, 100.0f);
		static const glm::vec2 Size(640, 480);
		static std::chrono::high_resolution_clock Clock;
		static bool IsRunning = true;
	};
};