#include "GameOverScreen.h"
#include "GameOverApplication.h"

GameOverScreen::GameOverScreen(std::shared_ptr<Game> game) : GameScreen(game, std::make_shared<GameOverApplication>(game))
{

}

void GameOverScreen::update(const double deltaTime) {
	app->update(deltaTime);
}

void GameOverScreen::render(const double deltaTime)
{
	app->render(deltaTime);
}