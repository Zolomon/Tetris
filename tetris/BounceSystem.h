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
		es.each<Body>([this](entityx::Entity entity, Body &body) {
			if (body.position.x + body.direction.x < 0 ||
				body.position.x + body.direction.x >= size.x)
				body.direction.x = -body.direction.x;
			if (body.position.y + body.direction.y < 0 ||
				body.position.y + body.direction.y >= size.y)
				body.direction.y = -body.direction.y;
		});
	}

private:
	glm::vec2 size;
};
