#pragma once

#include "entityx/entityx.h"
#include "Body.h"



// Updates a body's position and rotation.
struct BodySystem : public entityx::System<BodySystem> {
	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		es.each<Body>([dt](entityx::Entity entity, Body &body) {
			body.position += body.direction * static_cast<float>(dt);
			body.rotation += body.rotationd * static_cast<float>(dt);
		});
	};
};
