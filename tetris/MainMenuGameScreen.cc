#include "GameScreen.h"

MainMenuGameScreen::MainMenuGameScreen(std::shared_ptr<Game> game) : GameScreen(game, std::make_shared<MainMenuApplication>(game))
{

}

void MainMenuGameScreen::Update(const double deltaTime) {
	app->update(deltaTime);
}