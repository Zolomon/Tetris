#include "BodySystem.h"

void BodySystem::configure(entityx::EventManager &events) {
	events.subscribe<MoveLeftEvent>(*this);
	events.subscribe<MoveRightEvent>(*this);
}

void BodySystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) {
	es.each<Body>([dt](entityx::Entity entity, Body &body) {
		body.position += body.direction * static_cast<float>(dt);
		body.rotation += body.rotationd * static_cast<float>(dt);
	});
};

void BodySystem::receive(const MoveLeftEvent &moveLeft)
{

}

void BodySystem::receive(const MoveRightEvent &moveRight)
{

}