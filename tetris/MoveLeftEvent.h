#pragma once

#include "entityx/entityx.h"

struct MoveLeftEvent : entityx::Event<MoveLeftEvent>
{
	MoveLeftEvent() {}
};