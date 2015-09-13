#include "MenuRenderSystem.h"
#include "MenuItem.h"
#include "Body.h"
#include "SelectedMenuItem.h"


MenuRenderSystem::MenuRenderSystem(std::shared_ptr<Game> game) : game(game)
{

}


void MenuRenderSystem::update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt)
{
	game->BeginGraphics();
	game->DrawBitmap(game->bitmapDictionary[Resource::MainMenuBackground], 0, 0);

	es.each<MenuItem, Body>([this, dt](entityx::Entity entity, MenuItem& item, Body& body)
	{
		game->DrawString(item.text, RGB(0, 0, 0), body.position.x + 1, body.position.y + 1);

		game->DrawString(item.text, RGB(255, 255, 255), body.position.x, body.position.y);
	});

	es.each<MenuItem, SelectedMenuItem, Body>([this, dt](entityx::Entity entity, MenuItem& item, SelectedMenuItem&, Body& body)
	{
		game->DrawString(item.text, RGB(0, 0, 0), body.position.x + 1, body.position.y + 1);

		game->DrawString(item.text, RGB(255, 0, 0), body.position.x, body.position.y);
	});
	game->EndGraphics();
}
