#pragma once

#include "entityx/entityx.h"

// Emitted when two entities collide.
struct CollisionEvent {
	CollisionEvent(entityx::Entity left, entityx::Entity right) : left(left), right(right) {}

	entityx::Entity left, right;
};
