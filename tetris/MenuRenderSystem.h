#pragma once
#include "entityx/entityx.h"
#include "Game.h"

class MenuRenderSystem : public entityx::System<MenuRenderSystem> {
public:
	explicit MenuRenderSystem(std::shared_ptr<Game> game);

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

private:
	std::shared_ptr<Game> game;
};