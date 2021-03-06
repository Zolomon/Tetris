#include "MenuRenderSystem.h"
#include "MenuItem.h"
#include "Body.h"
#include "SelectedMenuItem.h"


MenuRenderSystem::MenuRenderSystem(std::shared_ptr<Game> game) : game(game)
{

}


void MenuRenderSystem::update(entityx::EntityManager& es, entityx::EventManager& events,
	entityx::TimeDelta dt)
{
	game->beginGraphics();
	game->drawBitmap(game->bitmapDictionary[Resource::MainMenuBackground], 0, 0);

	es.each<MenuItem, Body>([this, dt](entityx::Entity entity, MenuItem& item, Body& body)
	{
		game->drawString(item.text, RGB(0, 0, 0), 
			static_cast<int>(body.position.x + 1), 
			static_cast<LONG>(body.position.y + 1));
		game->drawString(item.text, RGB(255, 255, 255), 
			static_cast<LONG>(body.position.x), 
			static_cast<LONG>(body.position.y));
	});

	es.each<MenuItem, SelectedMenuItem, Body>([this, dt](entityx::Entity entity, MenuItem& item,
		SelectedMenuItem&, Body& body)
	{
		game->drawString(item.text, RGB(0, 0, 0), 
			static_cast<LONG>(body.position.x + 1), 
			static_cast<LONG>(body.position.y + 1));
		game->drawString(item.text, RGB(255, 0, 0), 
			static_cast<LONG>(body.position.x), 
			static_cast<LONG>(body.position.y));
	});
	game->endGraphics();
}
