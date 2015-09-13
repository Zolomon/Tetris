#include "Application.h"
#include "MainMenuApplication.h"
#include "MenuSpawnSystem.h"
#include "MenuRenderSystem.h"
#include "MenuInputSystem.h"

// Should not have used the entity system for the menu, totally overkill.

MainMenuApplication::MainMenuApplication(std::shared_ptr<Game> game)
{
	systems.add<MenuSpawnSystem>(game);

	systems.add<MenuInputSystem>(game);

	systems.add<MenuRenderSystem>(game);

	systems.configure();
}


void MainMenuApplication::update(entityx::TimeDelta dt)
{
	systems.update<MenuSpawnSystem>(dt);

	systems.update<MenuInputSystem>(dt);
}

void MainMenuApplication::render(entityx::TimeDelta dt)
{
	systems.update<MenuRenderSystem>(dt);
}

