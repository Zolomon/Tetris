#include "Piece.h"

Piece::Piece(PieceType type) : position(0, 0), type(type), isDestroyed(false)
{
	setupPiece(*this);
}

Piece::Piece(const Piece& other) : position(other.position), type(other.type), cellsInPiece(other.cellsInPiece), isDestroyed(other.isDestroyed)
{

}

Piece::Piece(Piece&& other) noexcept : position(other.position), type(other.type), cellsInPiece(other.cellsInPiece), isDestroyed(other.isDestroyed)
{
}

Piece& Piece::operator=(const Piece& other)
{
	Piece tmp(other);
	*this = std::move(tmp);
	return *this;
}

Piece& Piece::operator=(Piece&& other) noexcept
{
	std::swap(position, other.position);
	std::swap(type, other.type);
	std::swap(cellsInPiece, other.cellsInPiece);
	std::swap(isDestroyed, other.isDestroyed);
	return *this;
}

void Piece::setupPiece(Piece& piece)
{
	switch (piece.type)
	{
	case PieceType::I:
	{
		piece.cellsInPiece = std::vector<Cell>{
			Cell(0),Cell(1),Cell(0),Cell(0),
			Cell(0),Cell(1),Cell(0),Cell(0),
			Cell(0),Cell(1),Cell(0),Cell(0),
			Cell(0),Cell(1),Cell(0),Cell(0),
		};
		piece.size = 4;
	}
	break;
	case PieceType::J:
	{
		piece.cellsInPiece = std::vector<Cell>{
			Cell(0),Cell(2),Cell(0),
			Cell(0),Cell(2),Cell(0),
			Cell(2),Cell(2),Cell(0),
		};
		piece.size = 3;
	}
	break;
	case PieceType::L:
	{
		piece.cellsInPiece = std::vector<Cell>{
			Cell(0),Cell(3),Cell(0),
			Cell(0),Cell(3),Cell(0),
			Cell(0),Cell(3),Cell(3)
		};

		piece.size = 3;
	}
	break;
	case PieceType::O:
	{
		piece.cellsInPiece = std::vector<Cell>{
			Cell(4),Cell(4),
			Cell(4),Cell(4),
		};
		piece.size = 2;
	}
	break;
	case PieceType::S:
	{
		piece.cellsInPiece = std::vector<Cell>{
			Cell(0),Cell(0),Cell(0),
			Cell(0),Cell(5),Cell(5),
			Cell(5),Cell(5),Cell(0),
		};
		piece.size = 3;
	}
	break;
	case PieceType::Z:
	{
		piece.cellsInPiece = std::vector<Cell>{
			Cell(0),Cell(0),Cell(0),
			Cell(6),Cell(6),Cell(0),
			Cell(0),Cell(6),Cell(6),
		};
		piece.size = 3;
	}
	break;
	case PieceType::T:
	{
		piece.cellsInPiece = std::vector<Cell>{
			Cell(0),Cell(0),Cell(0),
			Cell(7),Cell(7),Cell(7),
			Cell(0),Cell(7),Cell(0),
		};
		piece.size = 3;
	}
	break;
	}
}

void Piece::rotate()
{
	std::vector<Cell> newCells;

	int n = size;

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			newCells.push_back(cellsInPiece[y + (n - x - 1) * n]);
		}
	}

	cellsInPiece = newCells;
}