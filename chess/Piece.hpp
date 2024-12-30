
#pragma once

#include <string>

enum Colour {
	NO_COLOUR	= ' ',
	WHITE		= 'w',
	BLACK		= 'b'
};

enum PieceType {
	NO_TYPE = ' ',
	PAWN	= 'P',
	BISHOP	= 'B',
	KNIGHT	= 'N',
	ROOK	= 'R',
	QUEEN	= 'Q',
	KING	= 'K'
};

class Piece {
public:
	char colour = NO_COLOUR;
	char type = NO_TYPE;

	static const Piece NO_PIECE;

	Piece();
	Piece(Colour colour, PieceType type);

	bool equals(const Piece& piece) const;
	std::string getSymbol() const;
};