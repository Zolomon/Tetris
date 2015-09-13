#include "RenderSystem.h"
#include "Body.h"
#include "ScoreScreen.h"
#include <tchar.h>
#include "Board.h"
#include "Piece.h"
#include "Utils.h"

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
				if (y < Settings::Game::DisabledBlockThreshold)
				{
					this->target->DrawBitmap(
						this->target->bitmapDictionary[Resource::DisabledBlock],
						x * (Settings::Game::TileSize.x + Settings::Game::TileOffset.x) +
								Settings::Game::BoardOffset.x,
								y * (Settings::Game::TileSize.y + Settings::Game::TileOffset.y) +
								Settings::Game::BoardOffset.y);
				}
				else
				{
					this->target->DrawBitmap(
						this->target->bitmapDictionary[
							Utils::GetResourceForPieceType(
								board.cells[x + y * Settings::Game::Columns].type)],
						x * (Settings::Game::TileSize.x + Settings::Game::TileOffset.x) +
								Settings::Game::BoardOffset.x,
								y * (Settings::Game::TileSize.y + Settings::Game::TileOffset.y) +
								Settings::Game::BoardOffset.y);
				}
				/*std::wstring nbr = std::to_wstring(x + y * Settings::Game::Columns);
				this->target->DrawString(nbr, RGB(0, 0, 0), x * (Settings::Game::TileSize.x + Settings::Game::TileOffset.x) +
					Settings::Game::BoardOffset.x, y * (Settings::Game::TileSize.y + Settings::Game::TileOffset.y) +
					Settings::Game::BoardOffset.y);
				this->target->DrawString(nbr, RGB(255, 255, 255), x * (Settings::Game::TileSize.x + Settings::Game::TileOffset.x) +
					Settings::Game::BoardOffset.x - 1, y * (Settings::Game::TileSize.y + Settings::Game::TileOffset.y) +
					Settings::Game::BoardOffset.y - 1);*/
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
					this->target->DrawBitmap(target->bitmapDictionary[
						Utils::GetResourceForPieceType(piece.cellsInPiece[x + y * piece.size].type)],
						drawX, drawY);
				}

				/*std::wstring nbr = std::to_wstring(x + y * piece.size);
				this->target->DrawString(nbr, RGB(0, 0, 0), drawX, drawY);
				this->target->DrawString(nbr, RGB(255, 255, 255), drawX - 1, drawY - 1);*/
			}
		}
	});

	es.each<ScoreScreen>([this](entityx::Entity entity, ScoreScreen &scoreScreen)
	{
		int itemOffset = 0;
		int itemOffsetDistance = 24;
		std::wstring highScore = _T("High Score: ");
		highScore += std::to_wstring(scoreScreen.highScore);
		this->target->DrawString(highScore, RGB(0, 0, 0), scoreScreen.position.x, scoreScreen.position.y);
		this->target->DrawString(highScore, RGB(255, 255, 255), scoreScreen.position.x - 1, scoreScreen.position.y - 1);

		itemOffset += itemOffsetDistance;

		std::wstring score = _T("Score: ");
		score += std::to_wstring(scoreScreen.score);
		this->target->DrawString(score, RGB(0, 0, 0), scoreScreen.position.x, scoreScreen.position.y + itemOffset);
		this->target->DrawString(score, RGB(255, 255, 255), scoreScreen.position.x - 1, scoreScreen.position.y + itemOffset - 1);

		itemOffset += itemOffsetDistance;

		std::wstring clearedRows = _T("Rows to next level: ");
		clearedRows += std::to_wstring(Settings::Game::RowsPerLevel - scoreScreen.clearedRows);
		this->target->DrawString(clearedRows, RGB(0, 0, 0), scoreScreen.position.x, scoreScreen.position.y + itemOffset);
		this->target->DrawString(clearedRows, RGB(255, 255, 255), scoreScreen.position.x - 1, scoreScreen.position.y + itemOffset - 1);

		itemOffset += itemOffsetDistance;

		std::wstring level = _T("Level: ");
		level += std::to_wstring(scoreScreen.currentLevel);
		this->target->DrawString(level, RGB(0, 0, 0), scoreScreen.position.x, scoreScreen.position.y + itemOffset);
		this->target->DrawString(level, RGB(255, 255, 255), scoreScreen.position.x - 1, scoreScreen.position.y + itemOffset - 1);

		itemOffset += itemOffsetDistance;

		std::wstring highestLevel = _T("Highest level: ");
		highestLevel += std::to_wstring(scoreScreen.highestLevel);
		this->target->DrawString(highestLevel, RGB(0, 0, 0), scoreScreen.position.x, scoreScreen.position.y + itemOffset);
		this->target->DrawString(highestLevel, RGB(255, 255, 255), scoreScreen.position.x - 1, scoreScreen.position.y + itemOffset - 1);
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