
#pragma once

#include "Piece.hpp"
#include "Position.hpp"

class Move {
public:
    Position startPos;
    Position endPos;
    Piece startPiece;
    Piece endPiece;

    Move(Position startPos, Position endPos, Piece startPiece, Piece endPiece);
};

