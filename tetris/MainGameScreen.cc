#include "MainGameScreen.h"
#include "GameApplication.h"

MainGameScreen::MainGameScreen(std::shared_ptr<Game> game) : GameScreen(game, std::make_shared<GameApplication>(game))
{

}

void MainGameScreen::update(const double deltaTime) {
	app->restart = restart;
	app->update(deltaTime);
	if (!app->restart)
	{
		restart = false;
	}
}

void MainGameScreen::render(const double deltaTime)
{
	app->render(deltaTime);
}