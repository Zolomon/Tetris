#pragma once

#include "glm/glm.hpp"

struct Collideable {
	explicit Collideable(glm::vec2 size) : size(size) {}

	glm::vec2 size;
};
