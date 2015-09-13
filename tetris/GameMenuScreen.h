#pragma once
#include "GameScreen.h"

class GameMenuScreen : public GameScreen
{
public:
	GameMenuScreen(std::shared_ptr<Game> game);

	void Update(const double deltaTime) override;
	void Render(const double deltaTime) override;
};