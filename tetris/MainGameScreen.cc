#include "MainGameScreen.h"
#include "GameApplication.h"

MainGameScreen::MainGameScreen(std::shared_ptr<Game> game) : GameScreen(game, std::make_shared<GameApplication>(game))
{
	
}

void MainGameScreen::Update(const double deltaTime) {
	app->update(deltaTime);
}

void MainGameScreen::Render(const double deltaTime)
{
	app->render(deltaTime);
}