#pragma once

#include "entityx/entityx.h"

struct PieceSpawnEvent : entityx::Event<PieceSpawnEvent>
{
	PieceSpawnEvent() {}
};
