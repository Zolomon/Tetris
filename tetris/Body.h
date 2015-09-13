#pragma once
#include "glm/glm.hpp"

struct Body {
	Body(const glm::vec2 &position, const glm::vec2 &direction)
		: position(position), direction(direction) {}

	glm::vec2 position;
	glm::vec2 direction;
};