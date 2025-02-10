
#pragma once

#include <string>

namespace Chess {

    enum Colour {
	    NO_COLOUR,
	    WHITE,
	    BLACK
    };

    const std::string COLOUR_NAMES[] {
        "No Colour",
        "White",
        "Black"
    };


    const char COLOUR_SYMBOLS[] {
	    ' ',
	    'w',
	    'b'
    };

    const char COLOUR_FORWARD_DIRECTIONS[] {
	    0,
	    1,
	    -1
    };

    const char COLOUR_START_RANK[] {
        -1,
        0,
        7,
    };

    const char COLOUR_VALUE_MODIFIERS[] {
        0,
        1,
        -1
    };

    Colour getOppositeColour(Colour colour);
    std::string getColourName(Colour colour);

    enum PieceType {
	    NO_PIECE_TYPE,
	    PAWN,
	    BISHOP,
	    KNIGHT,
	    ROOK,
	    QUEEN,
	    KING
    };

    const char PIECE_TYPE_SYMBOLS[7] {
	    ' ',
	    'P',
	    'B',
	    'N',
	    'R',
	    'Q',
	    'K'
    };

    const char PIECE_VALUES[7] {
	    0,
	    1,
	    3,
	    3,
	    5,
	    9,
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
	    char getForwardDirection() const;
        char getStartRank() const;
	    char getValue() const;

	    bool equals(const Piece& piece) const;
        bool operator==(const Piece& piece) const;
        bool operator!=(const Piece& piece) const;
	    std::string getSymbol() const;

    private:
	    char colour : 4;
	    char type	: 4;
    };

}