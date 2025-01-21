
#pragma once

#include "Piece.hpp"
#include "ChessVector.hpp"

enum SpecialMoveType {
    NO_SPECIAL_MOVE_TYPE,
    EN_PASSANT,
    SHORT_CASTLE,
    LONG_CASTLE
};

class Move {
public:
    ChessVector startPos;
    ChessVector endPos;
    Piece endPiece;
    SpecialMoveType specialType;

    Move(ChessVector startPos, ChessVector endPos, Piece endPiece, SpecialMoveType specialType = NO_SPECIAL_MOVE_TYPE);

    bool operator==(const Move& move);
};

