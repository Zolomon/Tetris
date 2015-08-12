#pragma once

#include "Game.h"
#include "entityx/entityx.h"

class Game;

class ParticleRenderSystem : public entityx::System<ParticleRenderSystem> {
public:
	explicit ParticleRenderSystem(std::shared_ptr<Game> target);

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
	
private:
	std::shared_ptr<Game> target;
};