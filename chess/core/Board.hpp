
#pragma once

#include <string>

#include "Move.hpp"
#include "Position.hpp"
#include "Piece.hpp"

class Board {
public:
	Board(bool startingBoad = false);
	Board(const Board& board);

	bool equals(const Board& board) const;
	std::string toString() const;

	Piece getPiece(char rank, char file) const;
	Piece getPiece(Position position) const;
	void setPiece(char rank, char file, const Piece& piece);
	void setPiece(Position position, const Piece& piece);

	void doMove(const Move& move);

	void clear();
	void setToStartingBoard();

	//Position getKingPos(Colour colour);

private:
	Piece pieces[8][8]; // Row-major (Rank then file)

	Position whiteKingPos;
	Position blackKingPos;
};