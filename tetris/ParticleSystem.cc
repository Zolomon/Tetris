
#include "ParticleSystem.h"

void ParticleSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) {
	es.each<Particle>([dt](entityx::Entity entity, Particle &particle) {
		particle.alpha -= particle.d * static_cast<float>(dt);
		if (particle.alpha <= 0) {
			entity.destroy();
		}
	});
}