
#include "Move.hpp"

Move::Move(ChessVector startPos, ChessVector endPos, Piece endPiece) :
    startPos(startPos), endPos(endPos), endPiece(endPiece)
{}
