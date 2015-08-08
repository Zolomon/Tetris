#pragma once
#include "entityx/System.h"
#include "Game.h"
#include "RotateEvent.h"
#include "InstanDownEvent.h"
#include "MoveDownEvent.h"
#include "MoveLeftEvent.h"
#include "MoveRightEvent.h"

class InputSystem : public entityx::System<InputSystem>
{
	explicit InputSystem(std::shared_ptr<Game> game) : game(game) {}

public:
	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		auto commands = game->GetCommandsThisFrame();

		for (auto command : commands)
		{
			switch(command)
			{
			case Rotate:
				events.emit<RotateEvent>();
				break;
			case InstantDown:
				events.emit<InstantDownEvent>();
				break;
			case MoveDown:
				events.emit<MoveDownEvent>();
				break;
			case MoveLeft:
				events.emit<MoveLeftEvent>();
				break;
			case MoveRight:
				events.emit<MoveRightEvent>();
				break;
			}
		}
	}

private:
	std::shared_ptr<Game> game;
};