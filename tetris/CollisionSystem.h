#pragma once

#include "entityx/entityx.h"
#include "glm/glm.hpp"
#include "Settings.h"
#include "CollisionEvent.h"
#include "Body.h"
#include "Collideable.h"

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
		float radius;
		entityx::Entity entity;
	};

public:
	explicit CollisionSystem() : size(Settings::Window::Size) {
		size.x = size.x / PARTITIONS + 1;
		size.y = size.y / PARTITIONS + 1;
	}

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		reset();
		collect(es);
		collide(events);
	};

private:
	std::vector<std::vector<Candidate>> grid;
	glm::vec2 size;

	void reset() {
		grid.clear();
		grid.resize(static_cast<unsigned int>(size.x * size.y));
	}

	void collect(entityx::EntityManager &entities) {
		entities.each<Body, Collideable>([this](entityx::Entity entity, Body &body, Collideable &collideable) {
			unsigned int
				left = static_cast<int>(body.position.x - collideable.radius) / PARTITIONS,
				top = static_cast<int>(body.position.y - collideable.radius) / PARTITIONS,
				right = static_cast<int>(body.position.x + collideable.radius) / PARTITIONS,
				bottom = static_cast<int>(body.position.y + collideable.radius) / PARTITIONS;
			Candidate candidate{ body.position, collideable.radius, entity };
			unsigned int slots[4] = {
				left + top * size.x,
				right + top * size.x,
				left + bottom * size.x,
				right + bottom * size.x,
			};
			grid[slots[0]].push_back(candidate);
			if (slots[0] != slots[1]) grid[slots[1]].push_back(candidate);
			if (slots[1] != slots[2]) grid[slots[2]].push_back(candidate);
			if (slots[2] != slots[3]) grid[slots[3]].push_back(candidate);
		});
	}

	void collide(entityx::EventManager &events) {
		for (const std::vector<Candidate> &candidates : grid) {
			for (const Candidate &left : candidates) {
				for (const Candidate &right : candidates) {
					if (left.entity == right.entity) continue;
					if (collided(left, right))
						events.emit<CollisionEvent>(left.entity, right.entity);
				}
			}
		}
	}

	float length(const glm::vec2 &v) {
		return std::sqrt(v.x * v.x + v.y * v.y);
	}

	bool collided(const Candidate &left, const Candidate &right) {
		return length(left.position - right.position) < left.radius + right.radius;
	}
};