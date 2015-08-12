#pragma once
#include "entityx/entityx.h"
#include "glm/glm.hpp"
#include "Body.h"
#include "Settings.h"

// Bounce bodies off the edge of the screen.
class BounceSystem : public entityx::System<BounceSystem> {
public:
	explicit BounceSystem();

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

private:
	glm::vec2 size;
};
