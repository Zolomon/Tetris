#pragma once
#include <vector>
#include "Cell.h"
#include "PieceType.h"
#include "glm/glm.hpp"

struct Piece
{
	explicit Piece(PieceType type);
	Piece(const Piece& other);
	Piece(Piece&& other) noexcept;
	Piece& operator= (const Piece& other);
	Piece& operator= (Piece&& other) noexcept;
	static void setupPiece(Piece& piece);
	void rotate();

	glm::vec2 position;
	PieceType type;
	std::vector<Cell> cellsInPiece;
	int size;
	bool isDestroyed;
};