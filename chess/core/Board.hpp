
#pragma once

#include <string>
#include <list>

#include "Move.hpp"
#include "ChessVector.hpp"
#include "Piece.hpp"

class Board {
public:
    Board(bool startingBoad = false);
    Board(const Board& board);

    bool equals(const Board& board) const;
    std::string toString() const;

    Piece getPiece(char rank, char file) const;
    Piece getPiece(ChessVector position) const;
    void setPiece(char rank, char file, const Piece& piece);
    void setPiece(ChessVector position, const Piece& piece);

    void clear();
    void setToStartingBoard();

    ChessVector getKingPos(Colour colour);
    bool isPiecePinned(ChessVector position);
    bool doesMoveCheckOwnKing(const Move& move);

    void getTargetedSquares(std::list<ChessVector>& targetedSquares, ChessVector position);
    void getMoves(std::list<Move>& moves, ChessVector position, bool useSelfCheckFilter = true);

    void doMove(const Move& move);

private:
    Piece pieces[8][8]; // Row-major (Rank then file)

    ChessVector whiteKingPos = ChessVector::INVALID_VEC;
    ChessVector blackKingPos = ChessVector::INVALID_VEC;

    void addTargetedSquaresByPawn(std::list<ChessVector>& targetedSquares, ChessVector position);
    void addTargetedSquaresByBishop(std::list<ChessVector>& targetedSquares, ChessVector position);
    void addTargetedSquaresByKnight(std::list<ChessVector>& targetedSquares, ChessVector position);
    void addTargetedSquaresByRook(std::list<ChessVector>& targetedSquares, ChessVector position);
    void addTargetedSquaresByQueen(std::list<ChessVector>& targeteSquares, ChessVector position);
    void addTargetedSquaresByKing(std::list<ChessVector>& targetedSquares, ChessVector position);

    void getPawnMoves(std::list<Move>& moves, ChessVector position, bool useSelfCheckFilter);
};