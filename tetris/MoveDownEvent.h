#pragma once

#include "entityx/entityx.h"

struct MoveDownEvent : entityx::Event<MoveDownEvent>
{
	//MoveDownEvent() : es(entityx::EventManager()) {}
	MoveDownEvent(entityx::EntityManager &es) : es(es) {}

	entityx::EntityManager &es;
};