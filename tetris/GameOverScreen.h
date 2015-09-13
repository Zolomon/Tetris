#pragma once
#include "GameScreen.h"

class GameOverScreen : public GameScreen
{
public:
	GameOverScreen(std::shared_ptr<Game> game);

	void Update(const double deltaTime) override;
	void Render(const double deltaTime) override;
};