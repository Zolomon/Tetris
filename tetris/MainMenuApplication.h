#pragma once
#include "Application.h"
#include "Game.h"

class MainMenuApplication : public Application
{
public:
	explicit MainMenuApplication(std::shared_ptr<Game> game);

	void update(entityx::TimeDelta dt) override;
	void render(entityx::TimeDelta dt) override;
};