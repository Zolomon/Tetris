#pragma once

#include "entityx/entityx.h"

struct MoveDownEvent : entityx::Event<MoveDownEvent>
{
	explicit MoveDownEvent(entityx::EntityManager &es) : es(es) {}

	entityx::EntityManager &es;
};