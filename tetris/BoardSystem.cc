#include "BoardSystem.h"
#include "Board.h"
#include "Piece.h"
#include "Utils.h"
#include "ScoreEvent.h"
#include "GameScreenType.h"
#include "ScoreScreen.h"

void BoardSystem::configure(entityx::EventManager& events)
{
	events.subscribe<MoveLeftEvent>(*this);
	events.subscribe<MoveRightEvent>(*this);
	events.subscribe<MoveDownEvent>(*this);
	events.subscribe<InstantDownEvent>(*this);
	events.subscribe<RotateEvent>(*this);
	events.subscribe<RestartEvent>(*this);
}

BoardSystem::BoardSystem(std::shared_ptr<Game> target) : target(target), currentTime(0), pieceMoveDownStartTime(0), gameOver(false)
{
}

bool BoardSystem::isMergable(Piece& piece)
{
	for (int y = 0; y < piece.size; y++)
	{
		for (int x = 0; x < piece.size; x++)
		{
			// TODO: Should never be possible to go out of bounds
			size_t xx = static_cast<size_t>(piece.position.x + x);
			size_t yy = static_cast<size_t>(piece.position.y + y);
			size_t index = static_cast<size_t>(xx + yy * Settings::Game::Columns);
			if (index >= this->board.component<Board>()->cells.size())
			{
				continue;
			}
			auto boardType = this->board.component<Board>()->cells[index].type;
			auto cellType = piece.cellsInPiece[x + y * piece.size].type;
			if (boardType != 0 && cellType != 0)
			{
				return false;
			}
		}
	}

	return true;
}

void BoardSystem::merge(Piece& piece)
{
	if (isMergable(piece))
	{
		for (int y = 0; y < piece.size; y++)
		{
			for (int x = 0; x < piece.size; x++)
			{
				if (piece.cellsInPiece[x + y * piece.size].type != 0)
				{
					auto xx = piece.position.x + x;
					auto yy = piece.position.y + y;
					auto index = static_cast<size_t>(xx + yy * Settings::Game::Columns);
					if (index < 0 || index >= board.component<Board>()->cells.size())
					{
						continue;
					}
					board.component<Board>()->cells[index] = Cell(piece.cellsInPiece[x + y * piece.size].type);
				}
			}
		}
	}
}


void BoardSystem::update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt)
{
	es.each<Piece>([this](entityx::Entity &entity, Piece&)
	{
		piece = entity;
	});

	es.each<Board>([this](entityx::Entity &entity, Board&)
	{
		board = entity;
	});

	es.each<ScoreScreen>([this](entityx::Entity &entity, ScoreScreen&)
	{
		scoreScreen = entity;
	});

	currentTime += dt;

	auto p = piece.component<Piece>();
	if (restart)
	{
		restart = false;
		gameOver = false;

		// Reset total score
		scoreScreen.component<ScoreScreen>()->score = 0;
		scoreScreen.component<ScoreScreen>()->currentLevel = 0;
		scoreScreen.component<ScoreScreen>()->clearedRows = 0;

		// Reset piece
		Piece *p = piece.component<Piece>().get();
		p->isDestroyed = true;

		// Clear board
		auto b = board.component<Board>().get();
		for (int y = 0; y < Settings::Game::Rows; y++)
		{
			for (int x = 0; x < Settings::Game::Columns; x++)
			{
				b->cells[x + y * Settings::Game::Columns].type = 0;
				b->cells[x + y * Settings::Game::Columns].isFilled = false;
			}
		}
	}

	if (p->isDestroyed)
	{
		p->position.y = 0;
		// TODO: Fix proper centering
		p->position.x = static_cast<float>(Settings::Game::Columns / 2 - (p->size / 2) - 1);
		p->isDestroyed = false;
		p->type = Utils::randomPieceType();
		Piece::setupPiece(*p.get());
	}

	auto movePieceDownDiff = pieceMoveDownStartTime + Settings::Game::MovePieceDownTime - currentTime;

	if (movePieceDownDiff <= 0)
	{
		events.emit<MoveDownEvent>(es);
		pieceMoveDownStartTime = currentTime;
	}

	std::vector<int> fullRows = getFullRows();
	scoreAndShiftRowsDown(fullRows, events);

	updateScoreScreen(fullRows.size());

	checkForGameOver();
}

void BoardSystem::checkForGameOver()
{
	int maxY = Settings::Game::Rows;
	for (int y = 0; y < Settings::Game::Rows; y++)
	{
		for (int x = 0; x < Settings::Game::Columns; x++)
		{
			if (board.component<Board>()->cells[x + (y)* Settings::Game::Columns].type != 0)
			{
				maxY = y;
				goto findHighestCell;
			}
		}
	}
findHighestCell:
	if (maxY < 4)
	{
		gameOver = true;
	}

	if (gameOver)
	{
		target->pushGameScreen(GameScreenType::GameOver);
	}
}

void BoardSystem::updateScoreScreen(int newRows)
{
	auto ss = scoreScreen.component<ScoreScreen>().get();
	ss->clearedRows += newRows;
	if (ss->clearedRows >= Settings::Game::RowsPerLevel)
	{
		ss->currentLevel++;
		ss->clearedRows = 0;
		Settings::Game::MovePieceDownTime = Utils::clampd(Settings::Game::MovePieceDownTime - 0.05, Settings::Game::MovePieceDownTimeMin, Settings::Game::MovePieceDownTimeMax);
	}
	if (ss->currentLevel > ss->highestLevel)
	{
		ss->highestLevel = ss->currentLevel;
	}
	if (ss->score > ss->highScore)
	{
		ss->highScore = ss->score;
	}
}

void BoardSystem::scoreAndShiftRowsDown(std::vector<int> fullRows, entityx::EventManager &events)
{
	for (auto row : fullRows)
	{
		for (int y = row; y > 1; y--)
		{
			for (int x = 0; x < Settings::Game::Columns; x++)
			{
				board.component<Board>()->cells[x + y * Settings::Game::Columns] =
					board.component<Board>()->cells[x + (y - 1) * Settings::Game::Columns];
				if (board.component<Board>()->cells[x + (y - 1) * Settings::Game::Columns].type != 0) {
					events.emit<ScoreEvent>();
				}
			}
		}
	}
}

std::vector<int> BoardSystem::getFullRows()
{
	std::vector<int> fullRows;
	for (int y = 0; y < Settings::Game::Rows; y++)
	{
		bool isFull = true;
		for (int x = 0; x < Settings::Game::Columns; x++)
		{
			isFull &= board.component<Board>()->cells[x + y * Settings::Game::Columns].type != 0;
		}
		if (isFull)
		{
			fullRows.push_back(y);
		}
	}
	return fullRows;
}

int BoardSystem::distanceToTopPieceEdge(Piece* p)
{
	for (int y = 0; y < p->size; y++)
	{
		for (int x = 0; x < p->size; x++)
		{
			if (p->cellsInPiece[x + y*p->size].type != 0)
			{
				return y;
			}
		}
	}
	assert(false);
	return -1;
}

int BoardSystem::distanceToBottomPieceEdge(Piece* p)
{
	for (int y = p->size - 1; y >= 0; y--)
	{
		for (int x = p->size - 1; x >= 0; x--)
		{
			if (p->cellsInPiece[x + y*p->size].type != 0)
			{
				return p->size - 1 - y;
			}
		}
	}
	assert(false);
	return -1;
}

int BoardSystem::distanceToLeftPieceEdge(Piece* p)
{
	int minX = std::numeric_limits<int>::max();

	for (int y = 0; y < p->size; y++)
	{
		for (int x = 0; x < p->size; x++)
		{
			if (p->cellsInPiece[x + y*p->size].type != 0)
			{
				if (x < minX) {
					minX = x;
				}
			}
		}
	}
	return minX;
}

int BoardSystem::distanceToRightPieceEdge(Piece* p)
{
	int maxX = std::numeric_limits<int>::max();
	for (int y = p->size - 1; y >= 0; y--)
	{
		for (int x = p->size - 1; x >= 0; x--)
		{
			if (p->cellsInPiece[x + y*p->size].type != 0)
			{
				if (p->size - 1 - x < maxX)
				{
					maxX = p->size - 1 - x;
				}
			}
		}
	}
	return maxX;
}

void BoardSystem::receive(const MoveLeftEvent& moveLeft)
{
	auto p = piece.component<Piece>().get();
	auto smallestX = distanceToLeftPieceEdge(p);
	auto preX = p->position.x;
	p->position.x = static_cast<float>(Utils::clampd(static_cast<double>(p->position.x - 1), -smallestX, Settings::Game::Columns));
	if (!isMergable(*p))
	{
		p->position.x = preX;
	}
}

void BoardSystem::receive(const MoveRightEvent& moveRight)
{
	auto p = piece.component<Piece>().get();
	auto largestX = distanceToRightPieceEdge(p);
	auto preX = p->position.x;
	p->position.x = static_cast<float>(Utils::clamp(static_cast<int>(p->position.x + 1), 0, Settings::Game::Columns - (p->size - largestX)));
	if (!isMergable(*p))
	{
		p->position.x = preX;
	}
}

void BoardSystem::receive(const MoveDownEvent& moveDownEvent)
{
	auto p = piece.component<Piece>().get();
	auto largestY = distanceToBottomPieceEdge(p);
	auto preY = p->position.y;
	p->position.y = static_cast<float>(Utils::clamp(static_cast<int>(p->position.y + 1), 0, Settings::Game::Rows - (p->size - largestY)));
	if (!isMergable(*p))
	{
		p->position.y = preY;
		merge(*p);
		p->isDestroyed = true;
	}
	// If we can't go down any further
	auto movePieceDownTimeDiff = this->pieceMoveDownStartTime + Settings::Game::MovePieceDownTime - currentTime;
	if (movePieceDownTimeDiff <= 0) {
		// TODO: Fix so that you can move left/right at the bottom row.
		if (p->position.y + p->size - distanceToBottomPieceEdge(p) - 1 == Settings::Game::Rows - 1)
		{
			merge(*p);
			p->isDestroyed = true;
		}
	}
	this->pieceMoveDownStartTime = this->currentTime;
	this->horizontalMovePieceStartTime = this->currentTime;
}

void BoardSystem::receive(const ScoreEvent& scoreEvent)
{
	score += scoreEvent.scorePerBlock;
}

void BoardSystem::receive(const InstantDownEvent& instantDownEvent)
{
	Piece *p = piece.component<Piece>().get();
	int newY = Settings::Game::Rows - p->size + distanceToBottomPieceEdge(p);
	for (int row = static_cast<int>(p->position.y); row < Settings::Game::Rows; row++)
	{
		for (int y = distanceToTopPieceEdge(p); y < p->size - distanceToBottomPieceEdge(p); y++) {
			int column = static_cast<int>(p->position.x + distanceToLeftPieceEdge(p));
			for (int x = distanceToLeftPieceEdge(p); x < p->size - distanceToRightPieceEdge(p); x++)
			{
				if (column > Settings::Game::Columns - 1 || row + y > Settings::Game::Rows - 1)
				{
					continue;
				}
				auto boardIndex = (column)+(row + y) * Settings::Game::Columns;
				auto cellIndex = x + y * p->size;
				if (board.component<Board>()->cells[boardIndex].type != 0 &&
					p->cellsInPiece[cellIndex].type != 0)
				{
					newY = row - 1;
					goto timeToMerge;
				}

				column++;
			}
		}
	}
timeToMerge:
	p->position.y = static_cast<float>(newY);
	merge(*p);
	p->isDestroyed = true;
}

void BoardSystem::receive(const PieceSpawnEvent& pieceSpawnEvent)
{
	pieceMoveDownStartTime = currentTime;
}

void BoardSystem::receive(const RestartEvent& restartEvent)
{
	restart = true;
}

void BoardSystem::receive(const RotateEvent& rotateEvent)
{
	auto p = piece.component<Piece>().get();
	if (p->type != PieceType::O) { // Ugly hack, should handle properly instead
		auto preLeft = distanceToLeftPieceEdge(p);
		auto preRight = distanceToRightPieceEdge(p);
		auto preTop = distanceToTopPieceEdge(p);
		auto preBot = distanceToBottomPieceEdge(p);
		p->rotate();
		if (isMergable(*p)) {
			if (p->position.x < 0)
			{
				p->position.x += preLeft;
			}
			else if (p->position.x + preRight + preLeft >= Settings::Game::Columns - 1)
			{
				p->position.x -= preRight;
			}
			if (p->position.y + preBot + preTop >= Settings::Game::Rows - 1)
			{
				p->position.y -= preBot;
			}
		}
		else
		{
			// TODO: Ugly hack, revert rotation by rotating another 270 degrees.
			p->rotate();
			p->rotate();
			p->rotate();
		}
	}
}