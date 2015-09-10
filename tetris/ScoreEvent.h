#pragma once
#include "entityx/Entity.h"

// Emitted when a block is destroyed.
struct ScoreEvent : entityx::Event<ScoreEvent>
{
	ScoreEvent() : scorePerBlock(500) {}

	long scorePerBlock;
};

