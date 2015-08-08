#pragma once

#include "entityx/entityx.h"
#include "SpawnSystem.h"
#include "BodySystem.h"
#include "BounceSystem.h"
#include "CollisionSystem.h"
#include "ExplosionSystem.h"
#include "ParticleSystem.h"
#include "RenderSystem.h"
#include "ParticleRenderSystem.h"
#include "ScoreSystem.h"


class Application : public entityx::EntityX {
public:
	explicit Application(std::shared_ptr<Game> game) {
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

	void update(entityx::TimeDelta dt) {
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
};