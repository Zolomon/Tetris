#include "MenuInputSystem.h"
#include "MenuItem.h"
#include "SelectedMenuItem.h"
#include "GameScreenType.h"
#include "Settings.h"

MenuInputSystem::MenuInputSystem(std::shared_ptr<Game> game) : game(game)
{

}


void MenuInputSystem::update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt)
{
	auto commandsThisFrame = game->GetCommandsThisFrame();

	for (auto&& command : commandsThisFrame)
	{
		switch (command)
		{
		case Down:
		{
			int index = -1;
			int maxIndex = -1;
			es.each<MenuItem, SelectedMenuItem>([this, &index](entityx::Entity& entity, MenuItem& menuItem, SelectedMenuItem&)
			{
				index = menuItem.index;
				entity.remove<SelectedMenuItem>();
			});
			es.each<MenuItem>([this, &maxIndex](entityx::Entity& entity, MenuItem& menuItem)
			{
				if (menuItem.index > maxIndex)
				{
					maxIndex = menuItem.index;
				}
			});
			index++;
			if (index > maxIndex)
			{
				index = 0;
			}
			es.each<MenuItem>([this, &index](entityx::Entity& entity, MenuItem& menuItem)
			{
				if (menuItem.index == index)
				{
					entity.assign<SelectedMenuItem>();
				}
			});
		}
		break;
		case Up:
		{
			int index = -1;
			int maxIndex = -1;
			es.each<MenuItem, SelectedMenuItem>([this, &index](entityx::Entity& entity, MenuItem& menuItem, SelectedMenuItem&)
			{
				index = menuItem.index;
				entity.remove<SelectedMenuItem>();
			});
			es.each<MenuItem>([this, &maxIndex](entityx::Entity& entity, MenuItem& menuItem)
			{
				if (menuItem.index > maxIndex)
				{
					maxIndex = menuItem.index;
				}
			});
			index--;
			if (index < 0)
			{
				index = maxIndex;
			}
			es.each<MenuItem>([this, &index](entityx::Entity& entity, MenuItem& menuItem)
			{
				if (menuItem.index == index)
				{
					entity.assign<SelectedMenuItem>();
				}
			});
		}
		break;
		case Enter:
		{
			es.each<MenuItem, SelectedMenuItem>([this](entityx::Entity &entity, MenuItem& menuItem, SelectedMenuItem&)
			{
				menuItem.execute(game);
			});
		}
		break;
		case Esc:
			PostQuitMessage(0);
			break;
		default: break;
		}
	}
}
