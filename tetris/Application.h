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
#include "Game.h"

class Game;

class Application : public entityx::EntityX {
public:
	virtual ~Application()
	{
	}

	virtual void update(entityx::TimeDelta dt) = 0;
};

class MainMenuApplication : public Application
{
public: 
	explicit MainMenuApplication(std::shared_ptr<Game> game);

	void update(entityx::TimeDelta dt) override;
};

class GameApplication : public Application {
public:
	explicit GameApplication(std::shared_ptr<Game> game);

	void update(entityx::TimeDelta dt) override;
};

