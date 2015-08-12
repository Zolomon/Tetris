#pragma once

#include "entityx/entityx.h"
#include "Body.h"
#include "MoveLeftEvent.h"
#include "MoveRightEvent.h"


// Updates a body's position and rotation.
struct BodySystem : public entityx::System<BodySystem>, public entityx::Receiver<BodySystem> {
public:
	void configure(entityx::EventManager &events) override;

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

	void receive(const MoveLeftEvent &moveLeft);

	void receive(const MoveRightEvent &moveRight);

private:

};
