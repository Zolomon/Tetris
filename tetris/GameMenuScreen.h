#pragma once
#include "GameScreen.h"

class GameMenuScreen : public GameScreen
{
public:
	explicit GameMenuScreen(std::shared_ptr<Game> game);

	void update(const double deltaTime) override;
	void render(const double deltaTime) override;
};