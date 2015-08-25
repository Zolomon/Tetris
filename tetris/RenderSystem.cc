#include "RenderSystem.h"
#include "Body.h"
#include "Renderable.h"
#include "ScoreScreen.h"
#include <tchar.h>

RenderSystem::RenderSystem(std::shared_ptr<Game> target) : target(target) { }

void RenderSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) {
	this->target->BeginGraphics();
	es.each<Body, Renderable>([this](entityx::Entity entity, Body &body, Renderable &renderable) {
		this->target->DrawBitmap(renderable.shape, body.position.x, body.position.y);
	});
	es.each<ScoreScreen>([this](entityx::Entity entity, ScoreScreen &scoreScreen)
	{
		std::wstring score = std::to_wstring(scoreScreen.score);
		this->target->DrawString(score, RGB(0, 0, 0), scoreScreen.position.x, scoreScreen.position.y);
		this->target->DrawString(score, RGB(255, 255, 255), scoreScreen.position.x - 1, scoreScreen.position.y - 1);
	});

	last_update += dt;
	frame_count++;
	std::wstring out;
	//if (last_update >= 0.5) {

	const double fps = frame_count / last_update;
	out = std::to_wstring(es.size()) + _T(" entities (") + std::to_wstring(static_cast<int>(fps)) + _T(" fps)");

	last_update = 0.0;
	frame_count = 0.0;
	//}
	this->target->DrawString(out, RGB(255, 0, 0), 10, 10);
	this->target->EndGraphics();
}