
#pragma once

#include "Board.hpp"
#include "Move.hpp"
#include "Piece.hpp"

class Player {
public:
    Player();

    Colour getColour();
    void setColour(Colour colour);

    virtual Move takeTurn(const Board& board, Colour colour) = 0;

private:
    Colour colour = NO_COLOUR;
};

