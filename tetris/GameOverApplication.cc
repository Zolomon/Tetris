#include "GameScreen.h"
#include "GameOverApplication.h"
#include <tchar.h>
#include "Settings.h"

GameOverApplication::GameOverApplication(std::shared_ptr<Game> game) : game(game), menuChoice(0) {

}

void GameOverApplication::update(entityx::TimeDelta dt) {
	auto commands = game->getCommandsThisFrame();
	// Ugly hack. 
	for (auto command : commands)
	{
		switch (command)
		{
		case Up:
		{ 
			menuChoice--;
			if (menuChoice < 0)
			{
				menuChoice = 1;
			}
		}
			break;
		case Space:
		case Enter: {
			int tmp = menuChoice;
			menuChoice = 0;
			switch (tmp)
			{
			case 0:
			{
				game->gameScreenDictionary[GameScreenType::Play]->restart = true;
				game->popGameScreen();
			}
			break;
			case 1:
				game->gameScreenDictionary[GameScreenType::Play]->restart = true;
				game->popGameScreen();
				game->popGameScreen();
				game->popGameScreen();
				break;
			}
			break;
		}
		case Down:
			menuChoice++;
			if (menuChoice > 1)
			{
				menuChoice = 0;
			}
			break;
		case Esc:
		{
			game->popGameScreen();
		}
		break;
		default:
			break;
		}
	}
}

void GameOverApplication::render(entityx::TimeDelta dt)
{
	game->beginGraphics();

	game->drawBitmap(game->bitmapDictionary[Resource::GameOverBackground], 0, 0);
	
	int offsetFromTop = 50;
	int itemOffsetY = offsetFromTop;
	int itemOffsetX = 50;
	int distanceToNextItem = 18;

	itemOffsetY += distanceToNextItem;
	std::wstring restartItem = _T("Restart");
	game->drawString(restartItem, RGB(0, 0, 0), itemOffsetX + 1, itemOffsetY + 1);
	game->drawString(restartItem, menuChoice == 0 ? RGB(255, 0, 0) : RGB(255, 255, 255), itemOffsetX, itemOffsetY);

	itemOffsetY += distanceToNextItem;
	std::wstring quitItem = _T("Quit");
	game->drawString(quitItem, RGB(0, 0, 0), itemOffsetX + 1, itemOffsetY + 1);
	game->drawString(quitItem, menuChoice == 1 ? RGB(255, 0, 0) : RGB(255, 255, 255), itemOffsetX, itemOffsetY);

	game->endGraphics();
}
