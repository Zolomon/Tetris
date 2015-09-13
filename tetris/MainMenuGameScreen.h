#pragma once
#include "GameScreen.h"

class MainMenuGameScreen : public GameScreen
{
public:
	explicit MainMenuGameScreen(std::shared_ptr<Game> game);

	void update(const double deltaTime) override;
	void render(const double deltaTime) override;
};