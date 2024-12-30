
#pragma once

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

	Piece();
	Piece(Colour colour, PieceType type);
};