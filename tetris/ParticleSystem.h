#pragma once

#include "entityx/entityx.h"
#include "Particle.h"

class ParticleSystem : public entityx::System<ParticleSystem> {
public:
	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		es.each<Particle>([dt](entityx::Entity entity, Particle &particle) {
			particle.alpha -= particle.d * dt;
			if (particle.alpha <= 0) {
				entity.destroy();
			}
		});
	}
};