#include "GameMenuScreen.h"
#include "GameMenuApplication.h"

GameMenuScreen::GameMenuScreen(std::shared_ptr<Game> game) : GameScreen(game, std::make_shared<GameMenuApplication>(game))
{

}

void GameMenuScreen::update(const double deltaTime) {
	app->update(deltaTime);
}

void GameMenuScreen::render(const double deltaTime)
{
	app->render(deltaTime);
}