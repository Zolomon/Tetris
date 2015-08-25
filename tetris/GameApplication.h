#pragma once
#include "Application.h"
#include "Game.h"

class GameApplication : public Application {
public:
	explicit GameApplication(std::shared_ptr<Game> game);

	void update(entityx::TimeDelta dt) override;
	void render(entityx::TimeDelta dt) override;
};
