
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
    ChessVector getPinDirection(ChessVector position);
    bool isPiecePinned(ChessVector position);
    int getNumChecks(Colour kingColour);
    bool isKingChecked(Colour kingColour);
    bool doesMoveCheckOwnKing(const Move& move);

    void getTargetedSquares(std::list<ChessVector>& targetedSquares, ChessVector position);
    void addMoves(std::list<Move>& moves, ChessVector position);
    void getMoves(std::list<Move>& moves, ChessVector position);

    void doMove(const Move& move);

private:
    Piece pieces[8][8]; // Row-major (Rank then file)
    ChessVector whiteKingPos = ChessVector::INVALID_VEC;
    ChessVector blackKingPos = ChessVector::INVALID_VEC;

    char numWhiteKingChecks;
    char numBlackKingChecks;

    void calculateNumChecks(Colour kingColour);

    void addTargetedSquaresByPawn(std::list<ChessVector>& targetedSquares, ChessVector position) const;
    void addTargetedSquaresByBishop(std::list<ChessVector>& targetedSquares, ChessVector position) const;
    void addTargetedSquaresByKnight(std::list<ChessVector>& targetedSquares, ChessVector position) const;
    void addTargetedSquaresByRook(std::list<ChessVector>& targetedSquares, ChessVector position) const;
    void addTargetedSquaresByQueen(std::list<ChessVector>& targeteSquares, ChessVector position) const;
    void addTargetedSquaresByKing(std::list<ChessVector>& targetedSquares, ChessVector position) const;

    void addPawnMoves(std::list<Move>& moves, ChessVector position);
    void addBishopMoves(std::list<Move>& moves, ChessVector position);
};