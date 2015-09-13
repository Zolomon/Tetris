#pragma once

#include "glm/glm.hpp"
#include <chrono>

namespace Settings
{
    namespace Window
    {
        static const glm::vec2 StartPosition(-670.0f, 0.0f);
        static const glm::vec2 Size(510, 510);
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
		static const int Rows = 24;
		static const int RowsPerLevel = 10;
		static const int DisabledBlockThreshold = 4;
		static double MovePieceDownTime = 1.25;
		static double MovePieceDownTimeMin = 0.5;
		static double MovePieceDownTimeMax = 1.25;
		
	};
};