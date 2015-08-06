#pragma once
#include "glm/glm.hpp"

struct Body {
	Body(const glm::vec2 &position, const glm::vec2 &direction, float rotationd = 0.0)
		: position(position), direction(direction), rotationd(rotationd) {}

	glm::vec2 position;
	glm::vec2 direction;
	float rotation = 0.0, rotationd;
};