#include "InputSystem.h"
#include "RotateEvent.h"
#include "InstanDownEvent.h"
#include "MoveDownEvent.h"
#include "MoveLeftEvent.h"
#include "MoveRightEvent.h"

InputSystem::InputSystem(std::shared_ptr<Game> game) : game(game) {}

void InputSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) {
	auto commands = game->GetCommandsThisFrame();

	for (auto command : commands)
	{
		switch (command)
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