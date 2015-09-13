#pragma once
#include "Application.h"
#include "Game.h"

class GameOverApplication : public Application 
{
public:
	explicit GameOverApplication(std::shared_ptr<Game> game);

	void update(entityx::TimeDelta dt) override;
	void render(entityx::TimeDelta dt) override;
private:
	std::shared_ptr<Game> game;
	int menuChoice;
};
