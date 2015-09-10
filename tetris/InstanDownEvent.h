#pragma once

#include "entityx/entityx.h"

struct InstantDownEvent : entityx::Event<InstantDownEvent>
{
	InstantDownEvent() {}
};