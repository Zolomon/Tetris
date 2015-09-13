#pragma once

#include "entityx/entityx.h"
#include "Settings.h"
#include "RestartEvent.h"

class SpawnSystem : public entityx::System<SpawnSystem>, public entityx::Receiver<SpawnSystem> {
public:
	explicit SpawnSystem(int count);

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
private:
	glm::vec2 size;
};
