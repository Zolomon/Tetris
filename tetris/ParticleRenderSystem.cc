#include "ParticleRenderSystem.h"
#include "Particle.h"
#include "Body.h"

ParticleRenderSystem::ParticleRenderSystem(std::shared_ptr<Game> target) : target(target) {}

void ParticleRenderSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) {
	es.each<Particle, Body>([&](entityx::Entity entity, Particle &particle, Body &body) {
		const float r = particle.radius;
		/*vertices.append(sf::Vertex(body.position + glm::vec2(-r, -r), particle.colour));
		vertices.append(sf::Vertex(body.position + glm::vec2(r, -r), particle.colour));
		vertices.append(sf::Vertex(body.position + glm::vec2(r, r), particle.colour));
		vertices.append(sf::Vertex(body.position + glm::vec2(-r, r), particle.colour));*/
		this->target->DrawBitmap(this->target->bitmapDictionary[Resource::RedBlock], body.position.x, body.position.y);
	});
	//target.Draw(vertices);
}
