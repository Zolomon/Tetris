#pragma once
#include "entityx/System.h"
#include "ScoreEvent.h"

class ScoreSystem : public entityx::System<ScoreSystem>, public entityx::Receiver<ScoreSystem>
{
public:
	void configure(entityx::EventManager &events) override;

	explicit ScoreSystem();

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

	void receive(const ScoreEvent &score);

private:
	long highScore;
};