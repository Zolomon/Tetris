#include "GameScreen.h"
#include "GameApplication.h"
#include "SpawnSystem.h"
#include "BodySystem.h"
#include "BounceSystem.h"
#include "CollisionSystem.h"
#include "ScoreSystem.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "BoardSystem.h"

GameApplication::GameApplication(std::shared_ptr<Game> game) {
	systems.add<SpawnSystem>(10);

	systems.add<BoardSystem>(game);

	systems.add<InputSystem>(game);

	systems.add<BodySystem>();

	systems.add<BounceSystem>();

	systems.add<CollisionSystem>();

	systems.add<ScoreSystem>();

	systems.add<RenderSystem>(game);

	systems.configure();
}

void GameApplication::update(entityx::TimeDelta dt) {
	systems.update<InputSystem>(dt);
	
	systems.update<SpawnSystem>(dt);

	systems.update<BoardSystem>(dt);

	systems.update<BodySystem>(dt);

	systems.update<BounceSystem>(dt);

	systems.update<CollisionSystem>(dt);

	systems.update<ScoreSystem>(dt);	
}

void GameApplication::render(entityx::TimeDelta dt)
{
	systems.update<RenderSystem>(dt);
}
