#pragma once
#include <unordered_set>
#include "CollisionEvent.h"
#include "Body.h"
#include "Renderable.h"
#include "Collideable.h"
#include "Utils.h"
#include "Particle.h"

// For any two colliding bodies, destroys the bodies and emits a bunch of bodgy explosion particles.
class ExplosionSystem : public entityx::System<ExplosionSystem>, public entityx::Receiver<ExplosionSystem> {
public:
	void configure(entityx::EventManager &events) override {
		events.subscribe<CollisionEvent>(*this);
	}

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		for (entityx::Entity entity : collided) {
			emit_particles(es, entity);
			entity.destroy();
		}
		collided.clear();
	}

	void emit_particles(entityx::EntityManager &es, entityx::Entity entity) {
		entityx::ComponentHandle<Body> body = entity.component<Body>();
		entityx::ComponentHandle<Renderable> renderable = entity.component<Renderable>();
		entityx::ComponentHandle<Collideable> collideable = entity.component<Collideable>();

		float area = (3.1459 * collideable->radius * collideable->radius) / 3.0;
		for (int i = 0; i < area; i++) {
			entityx::Entity particle = es.create();

			float rotationd = r(720, 180);
			if (std::rand() % 2 == 0) rotationd = -rotationd;

			float offset = r(collideable->radius, 1);
			float angle = r(360) * 3.1459 / 180.0;
			particle.assign<Body>(
				body->position + glm::vec2(offset * cos(angle), offset * sin(angle)),
				body->direction + glm::vec2(offset * 2 * cos(angle), offset * 2 * sin(angle)),
				rotationd);

			float radius = r(3, 1);
			particle.assign<Particle>(radius, radius / 2);
		}
	}

	void receive(const CollisionEvent &collision) {
		// Events are immutable, so we can't destroy the entities here. We defer
		// the work until the update loop.
		collided.insert(collision.left);
		collided.insert(collision.right);
	}

private:
	std::unordered_set<entityx::Entity> collided;
};