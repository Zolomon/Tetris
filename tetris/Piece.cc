#include "Piece.h"

Piece::Piece(PieceType type) : position(0, 0), type(type), isDestroyed(false)
{
	SetupPiece(*this);
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

void Piece::SetupPiece(Piece& piece)
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
			Cell(0),Cell(1),Cell(0),
			Cell(0),Cell(1),Cell(0),
			Cell(1),Cell(1),Cell(0),
		};
		piece.size = 3;
	}
	break;
	case PieceType::L:
	{
		piece.cellsInPiece = std::vector<Cell>{
			Cell(0),Cell(1),Cell(0),
			Cell(0),Cell(1),Cell(0),
			Cell(0),Cell(1),Cell(1)
		};

		piece.size = 3;
	}
	break;
	case PieceType::O:
	{
		piece.cellsInPiece = std::vector<Cell>{
			Cell(0),Cell(0),Cell(0),Cell(0),
			Cell(0),Cell(1),Cell(1),Cell(0),
			Cell(0),Cell(1),Cell(1),Cell(0),
			Cell(0),Cell(0),Cell(0),Cell(0),
		};
		piece.size = 4;
	}
	break;
	case PieceType::S:
	{
		piece.cellsInPiece = std::vector<Cell>{
			Cell(0),Cell(0),Cell(0),
			Cell(0),Cell(1),Cell(1),
			Cell(1),Cell(1),Cell(0),
		};
		piece.size = 3;
	}
	break;
	case PieceType::Z:
	{
		piece.cellsInPiece = std::vector<Cell>{
			Cell(0),Cell(0),Cell(0),
			Cell(1),Cell(1),Cell(0),
			Cell(0),Cell(1),Cell(1),
		};
		piece.size = 3;
	}
	break;
	case PieceType::T:
	{
		piece.cellsInPiece = std::vector<Cell>{
			Cell(0),Cell(0),Cell(0),
			Cell(1),Cell(1),Cell(1),
			Cell(0),Cell(1),Cell(0),
		};
		piece.size = 3;
	}
	break;
	}
}

void Piece::Rotate()
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