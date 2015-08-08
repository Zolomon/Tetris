#pragma once
#include "entityx/System.h"
#include "ScoreEvent.h"
#include "ScoreScreen.h"

class ScoreSystem : public entityx::System<ScoreSystem>, public entityx::Receiver<ScoreSystem>
{
public:
	void configure(entityx::EventManager &events) override {
		events.subscribe<ScoreEvent>(*this);
	}

	explicit ScoreSystem() { }

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		es.each<ScoreScreen>([this](entityx::Entity entity, ScoreScreen &scoreScreen)
		{
			scoreScreen.score = highScore;
		});
	}

	void receive(const ScoreEvent &score)
	{
		highScore += score.scorePerBlock;
	}

private:
	long highScore;
};