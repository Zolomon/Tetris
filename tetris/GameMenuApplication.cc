#include "GameScreen.h"
#include <tchar.h>
#include "GameMenuApplication.h"
#include "Settings.h"
#include "GameScreenType.h"

GameMenuApplication::GameMenuApplication(std::shared_ptr<Game> game) : game(game), menuChoice(0) {

}

void GameMenuApplication::update(entityx::TimeDelta dt) {
	auto commands = game->getCommandsThisFrame();
	int maxMenuChoice = 3;
	for (auto command : commands)
	{
		switch (command)
		{
		case Up: {
			menuChoice--;
			if (menuChoice < 0)
			{
				menuChoice = maxMenuChoice;
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
				game->pushGameScreen(GameScreenType::Play);
				break;
			case 1:
			{
				game->gameScreenDictionary[GameScreenType::Play]->restart = true;
				game->pushGameScreen(GameScreenType::Play);
			}
			break;
			case 2:
				game->popGameScreen();
				break;
			}
			break;
		}
		case Down:
			menuChoice = menuChoice + 1 % maxMenuChoice;
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

void GameMenuApplication::render(entityx::TimeDelta dt)
{
	game->beginGraphics();

	game->drawBitmap(game->bitmapDictionary[Resource::GameMenuBackground], 0, 0);
	
	int offsetFromTop = 50;
	int itemOffsetY = offsetFromTop;
	int itemOffsetX = 50;
	int distanceToNextItem = 18;
	std::wstring continueItem = _T("Continue");
	game->drawString(continueItem, RGB(0, 0, 0), itemOffsetX + 1, itemOffsetY + 1);
	game->drawString(continueItem, menuChoice == 0 ? RGB(255, 0, 0) : RGB(255, 255, 255), itemOffsetX, itemOffsetY);

	itemOffsetY += distanceToNextItem;
	std::wstring restartItem = _T("Restart");
	game->drawString(restartItem, RGB(0, 0, 0), itemOffsetX + 1, itemOffsetY + 1);
	game->drawString(restartItem, menuChoice == 1 ? RGB(255, 0, 0) : RGB(255, 255, 255), itemOffsetX, itemOffsetY);

	itemOffsetY += distanceToNextItem;
	std::wstring quitItem = _T("Quit");
	game->drawString(quitItem, RGB(0, 0, 0), itemOffsetX + 1, itemOffsetY + 1);
	game->drawString(quitItem, menuChoice == 2 ? RGB(255, 0, 0) : RGB(255, 255, 255), itemOffsetX, itemOffsetY);

	game->endGraphics();
}
