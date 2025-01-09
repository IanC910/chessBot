
#pragma once

#include <string>

enum Colour {
	NO_COLOUR,
	WHITE,
	BLACK
};

Colour getOppositeColour(Colour colour);

const char COLOUR_SYMBOLS[3] = {
	' ',
	'w',
	'b'
};

const char COLOUR_FORWARD_DIRECTIONS[3] = {
	0,
	1,
	-1
};

enum PieceType {
	NO_TYPE,
	PAWN,
	BISHOP,
	KNIGHT,
	ROOK,
	QUEEN,
	KING
};

const char PIECE_TYPE_SYMBOLS[7] = {
	' ',
	'P',
	'B',
	'N',
	'R',
	'Q',
	'K'
};

const char PIECE_VALUES[7] = {
	0,
	1,
	3,
	3,
	5,
	9,
	100
};

class Piece {
public:
	static const Piece NO_PIECE;

	Piece();
	Piece(const Piece& piece);
	Piece(Colour colour, PieceType type);

	Colour getColour() const;
	PieceType getType() const;
	char getForwardDirection() const;
	char getValue() const;

	bool equals(const Piece& piece) const;
	std::string getSymbol() const;

private:
	char colour : 4;
	char type	: 4;
};