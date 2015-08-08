#pragma once
#include <glm/detail/type_vec2.hpp>

struct ScoreScreen {
	ScoreScreen(const glm::vec2 &position)
		: position(position), score(0) {  }

	glm::vec2 position;
	long score;
};