#include "MainMenuApplication.h"
#include "MainMenuGameScreen.h"

MainMenuGameScreen::MainMenuGameScreen(std::shared_ptr<Game> game) : GameScreen(game, std::make_shared<MainMenuApplication>(game))
{

}

void MainMenuGameScreen::update(const double deltaTime) {
	app->update(deltaTime);
}

void MainMenuGameScreen::render(const double deltaTime)
{
	app->render(deltaTime);
}