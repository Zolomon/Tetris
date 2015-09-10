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

	namespace Game
	{
		static const int PieceSize = 4;
		static const glm::vec2 TileSize(16.0, 16.0);
		static const glm::vec2 TileOffset(2, 2);
		static const glm::vec2 BoardOffset(16, 16);
		static const int Columns = 10;
		static const int Rows = 20;
		static double MovePieceDownTime = 1.25;
	};
};