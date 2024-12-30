
#include "Piece.hpp"

const Piece Piece::NO_PIECE(NO_COLOUR, NO_TYPE);

Piece::Piece() {}

Piece::Piece(const Piece& piece) :
    colour(piece.colour), type(piece.type)
{}

Piece::Piece(Colour colour, PieceType type) :
    colour(colour), type(type)
{}

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