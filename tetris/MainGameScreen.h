#pragma once
#include "GameScreen.h"

class MainGameScreen : public GameScreen
{
public:
	explicit MainGameScreen(std::shared_ptr<Game> game);

	void update(const double deltaTime) override;
	void render(const double deltaTime) override;
};