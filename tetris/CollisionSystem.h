#pragma once

#include "entityx/entityx.h"
#include "glm/glm.hpp"

// Determines if two Collideable bodies have collided. If they have it emits a
// CollisionEvent. This is used by ExplosionSystem to create explosion
// particles, but it could be used by a SoundSystem to play an explosion
// sound, etc..
//
// Uses a fairly rudimentary 2D partition system, but performs reasonably well.
class CollisionSystem : public entityx::System<CollisionSystem> {
	static const int PARTITIONS = 200;

	struct Candidate {
		glm::vec2 position;
		glm::vec2 size;
		entityx::Entity entity;
	};

public:
	explicit CollisionSystem();

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

private:
	std::vector<std::vector<Candidate>> grid;
	glm::vec2 size;

	void reset();

	void collect(entityx::EntityManager &entities);

	void collide(entityx::EventManager &events);

	float length(const glm::vec2 &v);

	bool collided(const Candidate &left, const Candidate &right);
};