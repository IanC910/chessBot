
#include "Move.hpp"

using namespace Chess;

Move::Move() :
    startPos(Vector::INVALID), endPos(Vector::INVALID),
    endPiece(Piece::NO_PIECE), specialType(NO_SPECIAL_MOVE_TYPE)
{}

Move::Move(Vector startPos, Vector endPos, Piece endPiece, SpecialMoveType specialType) :
    startPos(startPos), endPos(endPos),
    endPiece(endPiece), specialType(specialType)
{}

bool Move::operator==(const Move& move) {
    return (
        startPos    == move.startPos &&
        endPos      == move.endPos &&
        endPiece    == move.endPiece &&
        specialType == move.specialType
    );
}

std::string Move::toString() {
    return startPos.toString() + endPos.toString();
}
