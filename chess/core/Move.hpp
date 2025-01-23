
#pragma once

#include <string>

#include "Piece.hpp"
#include "Vector.hpp"

namespace Chess {

    enum SpecialMoveType {
        NO_SPECIAL_MOVE_TYPE,
        EN_PASSANT,
        SHORT_CASTLE,
        LONG_CASTLE
    };

    class Move {
    public:
        Vector startPos;
        Vector endPos;
        Piece endPiece;
        SpecialMoveType specialType;

        Move();
        Move(Vector startPos, Vector endPos, Piece endPiece, SpecialMoveType specialType = NO_SPECIAL_MOVE_TYPE);

        bool operator==(const Move& move);

        std::string toString();
    };

}

