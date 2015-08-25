#pragma once

#include "entityx/entityx.h"

class Application : public entityx::EntityX {
public:
	virtual ~Application()
	{
	}

	virtual void update(entityx::TimeDelta dt) = 0;
	virtual void render(entityx::TimeDelta dt) = 0;
};