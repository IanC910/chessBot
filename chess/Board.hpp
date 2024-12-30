
#pragma once

#include <string>

#include "Position.hpp"
#include "Piece.hpp"

class Board {
public:
	Board();
	Board(const Board& board);

	bool equals(const Board& board) const;
	std::string toString() const;

	Piece getPiece(char rank, char file) const;
	void setPiece(char rank, char file, const Piece& piece);

	static Board* createDefaultBoard();

	//Position getKingPos(Colour colour);

private:
	Piece tiles[8][8]; // Row-major (Rank then file)
};