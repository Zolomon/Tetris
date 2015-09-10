#pragma once

#include "entityx/entityx.h"

struct RotateEvent : entityx::Event<RotateEvent>
{
	RotateEvent() {}
};