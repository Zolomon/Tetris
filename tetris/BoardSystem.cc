#include "BoardSystem.h"
#include "Board.h"
#include "Piece.h"
#include "Utils.h"

void BoardSystem::configure(entityx::EventManager& events)
{
	events.subscribe<MoveLeftEvent>(*this);
	events.subscribe<MoveRightEvent>(*this);
	events.subscribe<MoveDownEvent>(*this);
	events.subscribe<InstantDownEvent>(*this);
	events.subscribe<RotateEvent>(*this);
}

BoardSystem::BoardSystem(std::shared_ptr<Game> target) : target(target), currentTime(0), pieceMoveDownStartTime(0)
{
}

bool BoardSystem::isMergable(Piece& piece)
{
	for (int y = 0; y < piece.size; y++)
	{
		for (int x = 0; x < piece.size; x++)
		{
			// TODO: Should never be possible to go out of bounds
			int xx = (piece.position.x + x);
			int yy = (piece.position.y + y);
			auto index = xx + yy * Settings::Game::Columns;
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
					auto index = xx + yy * Settings::Game::Columns;
					if (index >= board.component<Board>()->cells.size())
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

	currentTime += dt;

	auto p = piece.component<Piece>();
	if (p->isDestroyed)
	{
		p->position.y = 0;
		// TODO: Fix proper centering
		p->position.x = Settings::Game::Columns / 2 - (p->size / 2) - 1;
		p->isDestroyed = false;
		p->type = Utils::RandomPieceType();
		Piece::SetupPiece(*p.get());
	}

	auto movePieceDownDiff = pieceMoveDownStartTime + Settings::Game::MovePieceDownTime - currentTime;

	if (movePieceDownDiff <= 0)
	{
		events.emit<MoveDownEvent>(es);
		pieceMoveDownStartTime = currentTime;
	}
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
	p->position.x = Utils::clamp(p->position.x - 1, -smallestX, Settings::Game::Columns);
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
	p->position.x = Utils::clamp(p->position.x + 1, 0, Settings::Game::Columns - (p->size - largestX));
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
	p->position.y = Utils::clamp(p->position.y + 1, 0, Settings::Game::Rows - (p->size - largestY));
	if (!isMergable(*p))
	{
		p->position.y = preY;
		merge(*p);
		p->isDestroyed = true;
	}
	// If we can't go down any further
	auto movePieceDownTimeDiff = this->pieceMoveDownStartTime + Settings::Game::MovePieceDownTime - currentTime;
	if (movePieceDownTimeDiff <= 0) {
		if (p->position.y + p->size - distanceToBottomPieceEdge(p) - 1 == Settings::Game::Rows - 1)
		{
			merge(*p);
			p->isDestroyed = true;
		}
	}
	this->pieceMoveDownStartTime = this->currentTime;
}

void BoardSystem::receive(const InstantDownEvent& instantDownEvent)
{
	Piece *p = piece.component<Piece>().get();
	int newY = Settings::Game::Rows - p->size + distanceToBottomPieceEdge(p);
	for (int row = p->position.y; row < Settings::Game::Rows; row++)
	{
		for (int y = distanceToTopPieceEdge(p); y < p->size - distanceToBottomPieceEdge(p); y++) {
			int column = p->position.x + distanceToLeftPieceEdge(p);
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
	p->position.y = newY;
	merge(*p);
	p->isDestroyed = true;
}

void BoardSystem::receive(const PieceSpawnEvent& pieceSpawnEvent)
{
	pieceMoveDownStartTime = currentTime;
}

void BoardSystem::receive(const RotateEvent& rotateEvent)
{
	auto p = piece.component<Piece>().get();
	if (p->type != PieceType::O) { // Ugly hack, should handle properly instead
		auto preLeft = distanceToLeftPieceEdge(p);
		auto preRight = distanceToRightPieceEdge(p);
		auto preTop = distanceToTopPieceEdge(p);
		auto preBot = distanceToBottomPieceEdge(p);
		p->Rotate();
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
			p->Rotate();
			p->Rotate();
			p->Rotate();
		}
	}
}




