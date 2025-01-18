
#include "Move.hpp"

Move::Move(ChessVector startPos, ChessVector endPos, Piece endPiece, SpecialMoveType specialType) :
    startPos(startPos), endPos(endPos), endPiece(endPiece), specialType(specialType)
{}

bool Move::operator==(const Move& move) {
    return (
        startPos    == move.startPos &&
        endPos      == move.endPos &&
        endPiece    == move.endPiece &&
        specialType == move.specialType
    );
}
