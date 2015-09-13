#include "SpawnSystem.h"
#include "Board.h"
#include "Piece.h"
#include "PieceSpawnEvent.h"
#include "Utils.h"
#include "ScoreScreen.h"

SpawnSystem::SpawnSystem(int count) : size(Settings::Window::Size)
{
}

void SpawnSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) {
	int boardCount = 0;
	es.each<Board>([&](entityx::Entity entity, Board& board) {++boardCount;});

	if (boardCount == 0) {
		entityx::Entity e = es.create();
		e.assign<Board>();
	}

	int pieceCount = 0;
	es.each<Piece>([&](entityx::Entity entity, Piece&piece) { ++pieceCount;	});

	if (pieceCount == 0)
	{
		entityx::Entity e = es.create();
		e.assign<Piece>(Utils::RandomPieceType());
		e.component<Piece>()->position.x = Settings::Game::Columns / 2 - e.component<Piece>()->size / 2;
		events.emit<PieceSpawnEvent>();
	}

	bool scoreScreenExists = false;
	es.each<ScoreScreen>([&](entityx::Entity entity, ScoreScreen&) { scoreScreenExists = true;});

	if (!scoreScreenExists)
	{
		entityx::Entity entity = es.create();
		entity.assign<ScoreScreen>(glm::vec2(Settings::Game::BoardOffset.x + (Settings::Game::TileOffset.x + Settings::Game::TileSize.x) * Settings::Game::Columns + Settings::Game::BoardOffset.x, 25));
	}
}