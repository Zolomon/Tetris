#pragma once
#include "Game.h"
#include "Particle.h"
#include "Body.h"
#include "entityx/entityx.h"

class ParticleRenderSystem : public entityx::System<ParticleRenderSystem> {
public:
	explicit ParticleRenderSystem(std::shared_ptr<Game> target) : target(target) {}

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
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
private:
	std::shared_ptr<Game> target;
};