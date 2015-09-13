#include "GameApplication.h"
#include "SpawnSystem.h"
#include "BoardSystem.h"
#include "InputSystem.h"
#include "ScoreSystem.h"
#include "RenderSystem.h"

GameApplication::GameApplication(std::shared_ptr<Game> game)  {
	systems.add<SpawnSystem>(10);

	systems.add<BoardSystem>(game);

	systems.add<InputSystem>(game);
	
	systems.add<ScoreSystem>();

	systems.add<RenderSystem>(game);

	systems.configure();
}

void GameApplication::update(entityx::TimeDelta dt) {
	if (restart)
	{
		events.emit<RestartEvent>();
		restart = false;
	}

	systems.update<InputSystem>(dt);
	
	systems.update<SpawnSystem>(dt);

	systems.update<BoardSystem>(dt);
	
	systems.update<ScoreSystem>(dt);	
}

void GameApplication::render(entityx::TimeDelta dt)
{
	systems.update<RenderSystem>(dt);
}
