
#pragma once

#include "Piece.hpp"
#include "ChessVector.hpp"

class Move {
public:
    ChessVector startPos;
    ChessVector endPos;
    Piece startPiece;
    Piece endPiece;

    Move(ChessVector startPos, ChessVector endPos, Piece startPiece, Piece endPiece);
};

