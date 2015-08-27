#pragma once
#include "GameScreen.h"

class MainGameScreen : public GameScreen
{
public:
	MainGameScreen(std::shared_ptr<Game> game);

	void Update(const double deltaTime) override;
	void Render(const double deltaTime) override;
};