#include "GameScreen.h"

GameApplication::GameApplication(std::shared_ptr<Game> game) {
	systems.add<SpawnSystem>(10);
	systems.add<BodySystem>();
	systems.add<BounceSystem>();
	systems.add<CollisionSystem>();/*
								   systems.add<ExplosionSystem>();
								   systems.add<ParticleSystem>();*/
	systems.add<ScoreSystem>();
	systems.add<RenderSystem>(game);

	/*systems.add<ParticleRenderSystem>(game);*/
	systems.configure();
}

void GameApplication::update(entityx::TimeDelta dt) {
	systems.update<SpawnSystem>(dt);
	systems.update<BodySystem>(dt);
	systems.update<BounceSystem>(dt);
	systems.update<CollisionSystem>(dt);/*
										systems.update<ExplosionSystem>(dt);
										systems.update<ParticleSystem>(dt);*/
	systems.update<ScoreSystem>(dt);
	systems.update<RenderSystem>(dt);
	/*systems.update<ParticleRenderSystem>(dt);*/
}