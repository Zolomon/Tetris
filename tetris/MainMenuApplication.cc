#include "Application.h"
#include "MainMenuApplication.h"
#include "MenuSpawnSystem.h"
#include "MenuRenderSystem.h"

MainMenuApplication::MainMenuApplication(std::shared_ptr<Game> game)
{
	systems.add<MenuSpawnSystem>();
	systems.add<MenuRenderSystem>(game);
	//systems.add<SpawnSystem>(10);
	//systems.add<BodySystem>();
	//systems.add<BounceSystem>();
	//systems.add<CollisionSystem>();/*
	//							   systems.add<ExplosionSystem>();
	//							   systems.add<ParticleSystem>();*/
	//systems.add<ScoreSystem>();
	//systems.add<RenderSystem>(game);

	/*systems.add<ParticleRenderSystem>(game);*/

	systems.configure();
}


void MainMenuApplication::update(entityx::TimeDelta dt)
{
	//systems.update<SpawnSystem>(dt);
	//systems.update<BodySystem>(dt);
	//systems.update<BounceSystem>(dt);
	//systems.update<CollisionSystem>(dt);/*
	//									systems.update<ExplosionSystem>(dt);
	//									systems.update<ParticleSystem>(dt);*/
	//systems.update<ScoreSystem>(dt);
	//systems.update<RenderSystem>(dt);
	/*systems.update<ParticleRenderSystem>(dt);*/
	systems.update<MenuSpawnSystem>(dt);
}

void MainMenuApplication::render(entityx::TimeDelta dt)
{
	systems.update<MenuRenderSystem>(dt);
}

