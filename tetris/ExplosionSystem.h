#pragma once
#include <unordered_set>
#include "CollisionEvent.h"
#include "Body.h"
#include "Renderable.h"
#include "Collideable.h"
#include "Utils.h"
#include "Particle.h"
#include "entityx/entityx.h"

#define M_PI (3.14159265358979323846)

// For any two colliding bodies, destroys the bodies and emits a bunch of bodgy explosion particles.
class ExplosionSystem : public entityx::System<ExplosionSystem>, public entityx::Receiver<ExplosionSystem> {
public:
	void configure(entityx::EventManager &events) override;

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

	void emit_particles(entityx::EntityManager &es, entityx::Entity entity);

	void receive(const CollisionEvent &collision);
private:
	std::unordered_set<entityx::Entity> collided;
};