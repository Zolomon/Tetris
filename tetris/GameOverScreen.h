#pragma once
#include "GameScreen.h"

class GameOverScreen : public GameScreen
{
public:
	explicit GameOverScreen(std::shared_ptr<Game> game);

	void update(const double deltaTime) override;
	void render(const double deltaTime) override;
};