#pragma once
#include "entityx/System.h"
#include "Game.h"

class InputSystem : public entityx::System<InputSystem>
{
public:
	explicit InputSystem(std::shared_ptr<Game> game);

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

private:
	std::shared_ptr<Game> game;
};