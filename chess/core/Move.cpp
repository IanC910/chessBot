
#include "Move.hpp"

Move::Move(ChessVector startPos, ChessVector endPos, Piece startPiece, Piece endPiece) :
    startPos(startPos), endPos(endPos), startPiece(startPiece), endPiece(endPiece)
{}
