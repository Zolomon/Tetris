#include "MenuSpawnSystem.h"
#include "Game.h"
#include "GameScreenType.h"
#include <tchar.h>
#include "MenuItem.h"
#include "Body.h"
#include "SelectedMenuItem.h"

MenuSpawnSystem::MenuSpawnSystem(std::shared_ptr<Game> game) : game(game), isMenuItemsCreated(false)
{
	
}

void MenuSpawnSystem::update(entityx::EntityManager& es, entityx::EventManager& events, 
	entityx::TimeDelta dt)
{
	if (!isMenuItemsCreated)
	{
		entityx::Entity playEntity = es.create();
		std::wstring text = _T("Play");
		
		std::function<void(std::shared_ptr<Game>)> playExec = [](std::shared_ptr<Game> game)
		{
			game->pushGameScreen(GameScreenType::GameMenu);
			game->pushGameScreen(GameScreenType::Play);
		};

		playEntity.assign<MenuItem>(0, text, playExec);

		playEntity.assign<Body>(glm::vec2(50.0f, 50.0f), glm::vec2(0.0f, 0.0f));
		playEntity.assign<SelectedMenuItem>();

		auto quitExec = [](std::shared_ptr<Game> game)
		{
			PostQuitMessage(0);
		};

		entityx::Entity quitEntity = es.create();
		std::wstring quitText = _T("Quit");
		quitEntity.assign<MenuItem>(1, quitText, quitExec);
		quitEntity.assign<Body>(glm::vec2(playEntity.component<Body>()->position.x, 
			static_cast<float>(playEntity.component<Body>()->position.x + 18)), 
			glm::vec2(0.0f, 0.0f));
		
		isMenuItemsCreated = true;
	}
}
