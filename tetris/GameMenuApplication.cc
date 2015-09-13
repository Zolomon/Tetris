#include "GameScreen.h"
#include <tchar.h>
#include "GameMenuApplication.h"
#include "Settings.h"
#include "GameScreenType.h"

GameMenuApplication::GameMenuApplication(std::shared_ptr<Game> game) : game(game), menuChoice(0) {

}

void GameMenuApplication::update(entityx::TimeDelta dt) {
	auto commands = game->GetCommandsThisFrame();
	int maxMenuChoice = 3;
	for (auto command : commands)
	{
		switch (command)
		{
		case Up: {
			this->menuChoice--;
			if (this->menuChoice < 0)
			{
				this->menuChoice = maxMenuChoice;
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
				game->PushGameScreen(GameScreenType::Play);
				break;
			case 1:
			{
				game->gameScreenDictionary[GameScreenType::Play]->restart = true;
				game->PushGameScreen(GameScreenType::Play);
			}
			break;
			case 2:
				game->PopGameScreen();
				break;
			}
			break;
		}
		case Down:
			this->menuChoice = this->menuChoice + 1 % maxMenuChoice;
			break;
		case Esc:
		{
			game->PopGameScreen();
		}
		break;
		default:
			break;
		}
	}
}

void GameMenuApplication::render(entityx::TimeDelta dt)
{
	game->BeginGraphics();

	game->DrawBitmap(game->bitmapDictionary[Resource::GameMenuBackground], 0, 0);
	
	int offsetFromTop = 50;
	int itemOffsetY = offsetFromTop;
	int itemOffsetX = 50;
	int distanceToNextItem = 18;
	std::wstring continueItem = _T("Continue");
	game->DrawString(continueItem, RGB(0, 0, 0), itemOffsetX + 1, itemOffsetY + 1);
	game->DrawString(continueItem, menuChoice == 0 ? RGB(255, 0, 0) : RGB(255, 255, 255), itemOffsetX, itemOffsetY);

	itemOffsetY += distanceToNextItem;
	std::wstring restartItem = _T("Restart");
	game->DrawString(restartItem, RGB(0, 0, 0), itemOffsetX + 1, itemOffsetY + 1);
	game->DrawString(restartItem, menuChoice == 1 ? RGB(255, 0, 0) : RGB(255, 255, 255), itemOffsetX, itemOffsetY);

	itemOffsetY += distanceToNextItem;
	std::wstring quitItem = _T("Quit");
	game->DrawString(quitItem, RGB(0, 0, 0), itemOffsetX + 1, itemOffsetY + 1);
	game->DrawString(quitItem, menuChoice == 2 ? RGB(255, 0, 0) : RGB(255, 255, 255), itemOffsetX, itemOffsetY);

	game->EndGraphics();
}
