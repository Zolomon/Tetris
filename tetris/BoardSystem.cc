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

BoardSystem::BoardSystem(std::shared_ptr<Game> target) : target(target)
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
			auto boardType = this->board.component<Board>()->cells[xx + yy * Settings::Game::Columns].type;
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
					board.component<Board>()->cells[xx + yy * Settings::Game::Columns] = Cell(1);
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
	}
}

void BoardSystem::receive(const InstantDownEvent& instantDownEvent)
{
	Piece *p = piece.component<Piece>().get();
	merge(*p);
	p->position.x = 0;
	p->position.y = 0;
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
}




