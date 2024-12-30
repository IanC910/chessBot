
#pragma once

#include <string>

#include "Move.hpp"
#include "Position.hpp"
#include "Piece.hpp"

class Board {
public:
	Board();
	Board(const Board& board);

	bool equals(const Board& board) const;
	std::string toString() const;

	Piece getPiece(char rank, char file) const;
	Piece getPiece(Position position) const;
	void setPiece(char rank, char file, const Piece& piece);
	void setPiece(Position position, const Piece& piece);

	void doMove(const Move& move);

	static Board* createStartingBoard();

	//Position getKingPos(Colour colour);

private:
	Piece tiles[8][8]; // Row-major (Rank then file)
};