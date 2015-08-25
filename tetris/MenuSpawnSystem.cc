#include "MenuSpawnSystem.h"

MenuSpawnSystem::MenuSpawnSystem() : isMenuItemsCreated(false)
{
	
}

void MenuSpawnSystem::update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt)
{
	if (!isMenuItemsCreated)
	{
		entityx::Entity entity = es.create();
		std::wstring text = _T("Play");
		entity.assign<MenuItem>(text);
		entity.assign<Body>(glm::vec2(50, 50), glm::vec2(0, 0), 0);
		entity.assign<SelectedMenuItem>();

		isMenuItemsCreated = true;
	}
}
