#pragma once
#include <glm/detail/type_vec2.hpp>

struct ScoreScreen {
	ScoreScreen(const glm::vec2 &position)
		: position(position), score(0), clearedRows(0), currentLevel(0), highestLevel(0), highScore(0) {  }

	glm::vec2 position;
	long score;
	int clearedRows;
	int currentLevel;
	int highestLevel;
	long highScore;
};