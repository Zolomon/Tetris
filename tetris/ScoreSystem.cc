#include "ScoreSystem.h"

void ScoreSystem::configure(entityx::EventManager &events) {
	events.subscribe<ScoreEvent>(*this);
}

ScoreSystem::ScoreSystem() { }

void ScoreSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) {
	es.each<ScoreScreen>([this](entityx::Entity entity, ScoreScreen &scoreScreen)
	{
		scoreScreen.score = highScore;
	});
}

void ScoreSystem::receive(const ScoreEvent &score)
{
	highScore += score.scorePerBlock;
}