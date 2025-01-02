
#pragma once

#include <string>

enum Colour {
	WHITE		= 0,
	BLACK		= 1,
	NO_COLOUR	= 2
};

Colour getOpposite(Colour colour);

const char COLOUR_SYMBOLS[3] = {
	'w',
	'b',
	' '
};

enum PieceType {
	PAWN	= 0,
	BISHOP	= 1,
	KNIGHT	= 2,
	ROOK	= 3,
	QUEEN	= 4,
	KING	= 5,
	NO_TYPE = 6
};

const char PIECE_TYPE_SYMBOLS[7] = {
	'P',
	'B',
	'N',
	'R',
	'Q',
	'K',
	' '
};

const char PIECE_VALUES[7] = {
	1,
	3,
	3,
	5,
	9,
	100,
	0
};

class Piece {
public:

	static const Piece NO_PIECE;

	Piece();
	Piece(const Piece& piece);
	Piece(Colour colour, PieceType type);

	Colour getColour() const;
	PieceType getType() const;
	char getValue() const;

	bool equals(const Piece& piece) const;
	std::string getSymbol() const;

private:
	char colour : 4;
	char type	: 4;
};