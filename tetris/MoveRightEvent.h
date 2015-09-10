#pragma once

#include "entityx/entityx.h"

struct MoveRightEvent : entityx::Event<MoveRightEvent>
{
	MoveRightEvent() {}
};