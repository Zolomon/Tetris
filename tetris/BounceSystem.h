#pragma once
#include "entityx/entityx.h"
#include "glm/glm.hpp"
#include "Body.h"
#include "Settings.h"

// Bounce bodies off the edge of the screen.
class BounceSystem : public entityx::System<BounceSystem> {
public:
	explicit BounceSystem() : size(Settings::Window::Size) {}

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		es.each<Body>([this, dt](entityx::Entity entity, Body &body) {
			if (body.position.x + (body.direction.x * static_cast<float>(dt)) < 0 ||
				body.position.x + 16 + (body.direction.x * static_cast<float>(dt)) >= size.x)
				body.direction.x = -body.direction.x;
			if (body.position.y + (body.direction.y * static_cast<float>(dt)) < 0 ||
				body.position.y + (body.direction.y * static_cast<float>(dt)) >= size.y - 50)
				body.direction.y = -body.direction.y;
		});
	}

private:
	glm::vec2 size;
};
