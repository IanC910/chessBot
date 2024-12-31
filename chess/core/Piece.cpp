
#include "Piece.hpp"

Colour getOpposite(Colour colour) {
    if (colour == NO_COLOUR) {
        return NO_COLOUR;
    }

    return (Colour)(1 - colour);
}

const Piece Piece::NO_PIECE(NO_COLOUR, NO_TYPE);

Piece::Piece() :
    colour(NO_COLOUR), type(NO_TYPE)
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

bool Piece::equals(const Piece& piece) const {
    return (
        this->colour == piece.colour &&
        this->type == piece.type
    );
}

std::string Piece::getSymbol() const {
    char symbol[3] = {COLOUR_SYMBOLS[colour], PIECE_TYPE_SYMBOLS[type], 0};
    return std::string(symbol);
}