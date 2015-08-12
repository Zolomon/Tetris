#include "CollisionSystem.h"

CollisionSystem::CollisionSystem() : size(Settings::Window::Size) {
	size.x = size.x / PARTITIONS + 1;
	size.y = size.y / PARTITIONS + 1;
}

void CollisionSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) {
	reset();
	collect(es);
	collide(events);
};


	void CollisionSystem::reset() {
		grid.clear();
		grid.resize(static_cast<unsigned int>(size.x * size.y));
	}

	void CollisionSystem::collect(entityx::EntityManager &entities) {
		entities.each<Body, Collideable>([this](entityx::Entity entity, Body &body, Collideable &collideable) {
			unsigned int
				left = static_cast<int>(body.position.x) / PARTITIONS,
				top = static_cast<int>(body.position.y) / PARTITIONS,
				right = static_cast<int>(body.position.x + collideable.size.x) / PARTITIONS,
				bottom = static_cast<int>(body.position.y + collideable.size.y) / PARTITIONS;
			Candidate candidate{ body.position, collideable.size, entity };
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

	void CollisionSystem::collide(entityx::EventManager &events) {
		for (const std::vector<Candidate> &candidates : grid) {
			for (const Candidate &left : candidates) {
				for (const Candidate &right : candidates) {
					if (left.entity == right.entity) continue;
					if (collided(left, right)) {
						events.emit<CollisionEvent>(left.entity, right.entity);
						events.emit<ScoreEvent>();
					}
				}
			}
		}
	}

	float CollisionSystem::length(const glm::vec2 &v) {
		return std::sqrt(v.x * v.x + v.y * v.y);
	}

	bool CollisionSystem::collided(const Candidate &left, const Candidate &right) {
		return (abs(left.position.x - right.position.x) * 2 < (left.size.x + right.size.x)) &&
			(abs(left.position.y - right.position.y) * 2 < (left.size.y + right.size.y));

		//return length(left.position - right.position) < left.size + right.size;
	}