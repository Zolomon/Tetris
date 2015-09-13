#include "InputSystem.h"
#include "RotateEvent.h"
#include "InstantDownEvent.h"
#include "MoveDownEvent.h"
#include "MoveLeftEvent.h"
#include "MoveRightEvent.h"

InputSystem::InputSystem(std::shared_ptr<Game> game) : game(game) {}

void InputSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) {
	auto commands = game->getCommandsThisFrame();

	for (auto command : commands)
	{
		switch (command)
		{
		case Up:
			events.emit<RotateEvent>();
			break;
		case Space:
			events.emit<InstantDownEvent>();
			break;
		case Down:
			events.emit<MoveDownEvent>(es);
			break;
		case Left:
			events.emit<MoveLeftEvent>();
			break;
		case Right:
			events.emit<MoveRightEvent>();
			break;
		case Esc:
		{
			game->popGameScreen();
		}
		break;
		default:
			break;
		}
	}
}