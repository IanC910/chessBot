
#pragma once

enum Colour {
	NO_COLOUR	= ' ',
	WHITE		= 'w',
	BLACK		= 'b'
};

enum PieceClass {
	NO_TYPE = ' ',
	PAWN	= 'P',
	BISHOP	= 'B',
	KNIGHT	= 'N',
	ROOK	= 'R',
	QUEEN	= 'Q',
	KING	= 'K'
};

struct Piece {
	char colour;
	char type;
};

const Piece NO_PIECE		= {NO_COLOUR, NO_TYPE};

const Piece WHITE_PAWN		= {WHITE, PAWN};
const Piece WHITE_BISHOP	= {WHITE, BISHOP};
const Piece WHITE_KNIGHT	= {WHITE, KNIGHT};
const Piece WHITE_ROOK		= {WHITE, ROOK};
const Piece WHITE_QUEEN		= {WHITE, QUEEN};
const Piece WHITE_KING		= {WHITE, KING};

const Piece BLACK_PAWN		= {BLACK, PAWN};
const Piece BLACK_BISHOP	= {BLACK, BISHOP};
const Piece BLACK_KNIGHT	= {BLACK, KNIGHT};
const Piece BLACK_ROOK		= {BLACK, ROOK};
const Piece BLACK_QUEEN		= {BLACK, QUEEN};
const Piece BLACK_KING		= {BLACK, KING};