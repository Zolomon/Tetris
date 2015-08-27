#include "SpawnSystem.h"

SpawnSystem::SpawnSystem(int count) : size(Settings::Window::Size), count(count)
{
}

void SpawnSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) {
	int c = 0;
	entityx::ComponentHandle<Collideable> collideable;
	es.each<Collideable>([&](entityx::Entity entity, Collideable&) { ++c; });

	bool scoreScreenExists = false;
	entityx::ComponentHandle<ScoreScreen> scoreScreen;
	es.each<ScoreScreen>([&](entityx::Entity entity, ScoreScreen&) { scoreScreenExists = true;});

	if (!scoreScreenExists)
	{
		entityx::Entity entity = es.create();
		entity.assign<ScoreScreen>(glm::vec2(100, 25));
	}

	for (int i = 0; i < count - c; i++) {
		entityx::Entity entity = es.create();

		// Mark as collideable (explosion particles will not be collideable).
		collideable = entity.assign<Collideable>(glm::vec2(16, 16));

		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> randomWidth(16, Settings::Window::Size.x);
		std::uniform_real_distribution<double> randomHeight(16, Settings::Window::Size.y);

		// "Physical" attributes.
		entity.assign<Body>(
			glm::vec2(randomWidth(mt), randomHeight(mt)),
			glm::vec2(r(100, -50), r(100, -50)));

		// Shape to apply to entity.
		Bitmap bmp = { 0 };
		entity.assign<Renderable>(bmp);
	}
}