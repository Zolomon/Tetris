#include "RenderSystem.h"
#include "Body.h"
#include "Renderable.h"
#include "ScoreScreen.h"
#include <tchar.h>
#include "Board.h"
#include "Piece.h"

RenderSystem::RenderSystem(std::shared_ptr<Game> target) : target(target) { }

void RenderSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) {
	this->target->BeginGraphics();

	target->DrawBitmap(target->bitmapDictionary[Resource::Background], 0, 0);

	es.each<Board>([this](entityx::Entity entity, Board& board)
	{
		for (int y = 0; y < Settings::Game::Rows; y++)
		{
			for (int x = 0; x < Settings::Game::Columns; x++)
			{
				switch (board.cells[x + y * Settings::Game::Columns].type)
				{
				case 0:
					this->target->DrawBitmap(this->target->bitmapDictionary[Resource::BlackBlock],
						x * (Settings::Game::TileSize.x + Settings::Game::TileOffset.x) + Settings::Game::BoardOffset.x,
						y * (Settings::Game::TileSize.y + Settings::Game::TileOffset.y) + Settings::Game::BoardOffset.y);
					break;
				case 1:
					this->target->DrawBitmap(this->target->bitmapDictionary[Resource::BlueBlock],
						x * (Settings::Game::TileSize.x + Settings::Game::TileOffset.x) + Settings::Game::BoardOffset.x,
						y * (Settings::Game::TileSize.y + Settings::Game::TileOffset.y) + Settings::Game::BoardOffset.y);
					break;
				case 2:
					this->target->DrawBitmap(this->target->bitmapDictionary[Resource::RedBlock],
						x * (Settings::Game::TileSize.x + Settings::Game::TileOffset.x) + Settings::Game::BoardOffset.x,
						y * (Settings::Game::TileSize.y + Settings::Game::TileOffset.y) + Settings::Game::BoardOffset.y);
					break;
				}
				
			}
		}
	});

	es.each<Piece>([this](entityx::Entity entity, Piece& piece)
	{
		for (int y = 0; y < piece.size; y++)
		{
			for (int x = 0; x < piece.size; x++)
			{
				auto drawX = (piece.position.x + x) * (Settings::Game::TileSize.x + Settings::Game::TileOffset.x) + Settings::Game::BoardOffset.x;
				auto drawY = (piece.position.y + y) * (Settings::Game::TileSize.y + Settings::Game::TileOffset.y) + Settings::Game::BoardOffset.y;
				if (piece.cellsInPiece[x + y * piece.size].type != 0) {
					this->target->DrawBitmap(target->bitmapDictionary[Resource::RedBlock], drawX, drawY);
				}

				std::wstring nbr = std::to_wstring(x + y * piece.size);
				this->target->DrawString(nbr, RGB(0, 0, 0), drawX, drawY);
				this->target->DrawString(nbr, RGB(255, 255, 255), drawX - 1, drawY - 1);
			}
		}


	});

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