#pragma once

#include "Game.h"
#include "entityx/entityx.h"

class Game;

// render all Renderable entities and draw some informational text.
class RenderSystem :public entityx::System<RenderSystem> {
public:
	explicit RenderSystem(std::shared_ptr<Game> target);

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

private:
	double last_update = 0.0;
	double frame_count = 0.0;
	std::shared_ptr<Game> target;
};