#include "ExplosionSystem.h"

void ExplosionSystem::configure(entityx::EventManager &events) {
	events.subscribe<CollisionEvent>(*this);
}

void ExplosionSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) {
	for (entityx::Entity entity : collided) {
		emit_particles(es, entity);
		entity.destroy();
	}
	collided.clear();
}

void ExplosionSystem::emit_particles(entityx::EntityManager &es, entityx::Entity entity) {
	entityx::ComponentHandle<Body> body = entity.component<Body>();
	entityx::ComponentHandle<Renderable> renderable = entity.component<Renderable>();
	entityx::ComponentHandle<Collideable> collideable = entity.component<Collideable>();

	////float area = (M_PI * collideable->size.x * collideable->size.y) / 3.0;
	//for (int i = 0; i < 10; i++) {
	//	entityx::Entity particle = es.create();

	//	float rotationd = r(720, 180);
	//	if (std::rand() % 2 == 0) rotationd = -rotationd;

	//	float offset = r(collideable->size.x, 1);
	//	float angle = r(360) * M_PI / 180.0;
	//	particle.assign<Body>(
	//		body->position + glm::vec2(offset * cos(angle), offset * sin(angle)),
	//		body->direction + glm::vec2(offset * 2 * cos(angle), offset * 2 * sin(angle)),
	//		rotationd);

	//	float radius = r(3, 1);
	//	//particle.assign<Particle>(radius, radius / 2);
	//}

}

void ExplosionSystem::receive(const CollisionEvent &collision) {
	// Events are immutable, so we can't destroy the entities here. We defer
	// the work until the update loop.
	collided.insert(collision.left);
	collided.insert(collision.right);
}