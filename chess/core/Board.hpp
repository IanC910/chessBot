
#pragma once

#include <string>
#include <list>

#include "Move.hpp"
#include "Position.hpp"
#include "Piece.hpp"

class Board {
public:
    Board(bool startingBoad = false);
    Board(const Board& board);

    bool equals(const Board& board) const;
    std::string toString() const;

    Piece getPiece(char rank, char file) const;
    Piece getPiece(Position position) const;
    void setPiece(char rank, char file, const Piece& piece);
    void setPiece(Position position, const Piece& piece);

    void clear();
    void setToStartingBoard();

    Position getKingPos(Colour colour);
    bool doesMoveCheckOwnKing(const Move& move);

    void getLegalMoves(std::list<Move>& legalMoves, Position position, Piece piece);

    void doMove(const Move& move);

private:
    Piece pieces[8][8]; // Row-major (Rank then file)

    Position whiteKingPos = Position::NO_POSITION;
    Position blackKingPos = Position::NO_POSITION;

    void getLegalPawnMoves(std::list<Move>& legalMoves, Position position, Piece piece);
};