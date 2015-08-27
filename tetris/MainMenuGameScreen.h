#pragma once
#include "GameScreen.h"

class MainMenuGameScreen : public GameScreen
{
public:
	MainMenuGameScreen(std::shared_ptr<Game> game);

	/*void OnLoad() override;
	void Loading() override;
	void OnLoaded() override;*/
	void Update(const double deltaTime) override;
	void Render(const double deltaTime) override;
	/*void Render(const double interpolation) override;
	void OnUnloading() override;
	void Unloading() override;
	void OnUnloaded() override;*/
};