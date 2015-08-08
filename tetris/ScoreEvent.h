#pragma once
#include "entityx/Entity.h"

// Emitted when a block is destroyed.
struct ScoreEvent {
	ScoreEvent() : scorePerBlock(500) {}

	long scorePerBlock;
};

