#pragma once

#include "entityx/entityx.h"
#include "Body.h"
#include "MoveLeftEvent.h"
#include "MoveRightEvent.h"
#include "MenuItem.h"
#include <tchar.h>
#include "Settings.h"
#include "SelectedMenuItem.h"
#include "Game.h"
#include <condition_variable>


// Updates a body's position and rotation.
class MenuSpawnSystem : public entityx::System<MenuSpawnSystem> {
public:
	explicit MenuSpawnSystem(std::shared_ptr<Game> game);
	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
	
private:
	bool isMenuItemsCreated;
	std::shared_ptr<Game> game;
};
