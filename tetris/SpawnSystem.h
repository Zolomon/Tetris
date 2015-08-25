#pragma once

#include "entityx/entityx.h"
#include "Collideable.h"
#include "Settings.h"
#include "Utils.h"
#include "Body.h"
#include "Renderable.h"
#include "ScoreScreen.h"

class SpawnSystem : public entityx::System<SpawnSystem> {
public:
	explicit SpawnSystem(int count);

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

private:
	glm::vec2 size;
	int count;
};
