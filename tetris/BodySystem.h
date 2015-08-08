#pragma once

#include "entityx/entityx.h"
#include "Body.h"
#include "MoveLeftEvent.h"
#include "MoveRightEvent.h"


// Updates a body's position and rotation.
struct BodySystem : public entityx::System<BodySystem>, public entityx::Receiver<BodySystem> {
public:
	void configure(entityx::EventManager &events) override {
		events.subscribe<MoveLeftEvent>(*this);
		events.subscribe<MoveRightEvent>(*this);
	}

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		es.each<Body>([dt](entityx::Entity entity, Body &body) {
			body.position += body.direction * static_cast<float>(dt);
			body.rotation += body.rotationd * static_cast<float>(dt);
		});
	};

	void receive(const MoveLeftEvent &moveLeft)
	{
		
	}

	void receive(const MoveRightEvent &moveRight)
	{

	}

private:

};
