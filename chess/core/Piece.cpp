
#include "Piece.hpp"

using namespace Chess;

Colour Chess::getOppositeColour(Colour colour) {
    switch (colour) {
        case WHITE:
            return BLACK;
        case BLACK:
            return WHITE;
        default:
            return NO_COLOUR;
    }
}

const Piece Piece::NO_PIECE(NO_COLOUR, NO_PIECE_TYPE);

Piece::Piece() :
    colour(NO_COLOUR), type(NO_PIECE_TYPE)
{}

Piece::Piece(const Piece& piece) :
    colour(piece.colour), type(piece.type)
{}

Piece::Piece(Colour colour, PieceType type) :
    colour(colour), type(type)
{}

Colour Piece::getColour() const {
    return (Colour)colour;
}

PieceType Piece::getType() const {
    return (PieceType)type;
}

char Piece::getForwardDirection() const {
    return COLOUR_FORWARD_DIRECTIONS[colour];
}

char Piece::getStartRank() const {
    char startRank = COLOUR_START_RANK[colour];
    if (type == PAWN) {
        startRank += getForwardDirection();
    }
    return startRank;
}

char Piece::getValue() const {
    return PIECE_VALUES[type];
}

bool Piece::equals(const Piece& piece) const {
    return (
        this->colour == piece.colour &&
        this->type == piece.type
    );
}

bool Piece::operator==(const Piece& piece) const {
    return equals(piece);
}

bool Piece::operator!=(const Piece& piece) const {
    return !equals(piece);
}

std::string Piece::getSymbol() const {
    char symbol[] = {COLOUR_SYMBOLS[colour], PIECE_TYPE_SYMBOLS[type], 0};
    return std::string(symbol);
}
