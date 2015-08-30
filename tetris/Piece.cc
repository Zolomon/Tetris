#include "Piece.h"

Piece::Piece(PieceType type) : position(0, 0), type(type)
{
	switch (type)
	{
	case PieceType::I:
	{
		cellsInPiece = std::vector<Cell>{
			Cell(0),Cell(1),Cell(0),Cell(0),
			Cell(0),Cell(1),Cell(0),Cell(0),
			Cell(0),Cell(1),Cell(0),Cell(0),
			Cell(0),Cell(1),Cell(0),Cell(0),
		};
		size = 4;
	}
	break;
	case PieceType::J:
	{
		cellsInPiece = std::vector<Cell>{
			Cell(0),Cell(1),Cell(0),
			Cell(0),Cell(1),Cell(0),
			Cell(1),Cell(1),Cell(0),
		};
		size = 3;
	}
	break;
	case PieceType::L:
	{
		cellsInPiece = std::vector<Cell>{
			Cell(0),Cell(1),Cell(0),
			Cell(0),Cell(1),Cell(0),
			Cell(0),Cell(1),Cell(1)
		};

		size =3;
	}
	break;
	case PieceType::O:
	{
		cellsInPiece = std::vector<Cell>{
			Cell(0),Cell(0),Cell(0),Cell(0),
			Cell(0),Cell(1),Cell(1),Cell(0),
			Cell(0),Cell(1),Cell(1),Cell(0),
			Cell(0),Cell(0),Cell(0),Cell(0),
		};
		size = 4;
	}
	break;
	case PieceType::S:
	{
		cellsInPiece = std::vector<Cell>{
			Cell(0),Cell(0),Cell(0),
			Cell(0),Cell(1),Cell(1),
			Cell(1),Cell(1),Cell(0),
		};
		size = 3;
	}
	break;
	case PieceType::Z:
	{
		cellsInPiece = std::vector<Cell>{
			Cell(0),Cell(0),Cell(0),
			Cell(1),Cell(1),Cell(0),
			Cell(0),Cell(1),Cell(1),
		};
		size = 3;
	}
	break;
	case PieceType::T:
	{
		cellsInPiece = std::vector<Cell>{
			Cell(0),Cell(0),Cell(0),
			Cell(1),Cell(1),Cell(1),
			Cell(0),Cell(1),Cell(0),
		};
		size = 3;
	}
	break;
	}
}

Piece::Piece(const Piece& other) : position(other.position), type(other.type), cellsInPiece(other.cellsInPiece)
{

}

Piece::Piece(Piece&& other) noexcept : position(other.position), type(other.type), cellsInPiece(other.cellsInPiece)
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
	return *this;
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