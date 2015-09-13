#pragma once

#include "entityx/entityx.h"

struct RestartEvent : entityx::Event<RestartEvent>
{
	RestartEvent() {}
};