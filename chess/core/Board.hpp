
#pragma once

#include <string>
#include <list>

#include "Move.hpp"
#include "ChessVector.hpp"
#include "Piece.hpp"

class Board {
public:
    Board();
    Board(const Board& board);

    bool equals(const Board& board) const;
    bool operator==(const Board& board) const;
    bool operator!=(const Board& board) const;
    std::string toString() const;

    void clearCache();

    Piece getPiece(char rank, char file) const;
    Piece getPiece(ChessVector position) const;
    void setPiece(char rank, char file, const Piece& piece);
    void setPiece(ChessVector position, const Piece& piece);

    void clear();
    void setToStartingBoard();

    ChessVector getKingPos(Colour colour) const;
    ChessVector getPinDirection(ChessVector position) const;
    bool isPiecePinned(ChessVector position) const;
    int getNumChecks(Colour kingColour);
    const std::list<ChessVector>* getPositionsCheckingKing(Colour kingColour);
    bool isKingChecked(Colour kingColour);
    bool getEnPassantFlag();

    void addSquaresSeenByPiece(std::list<ChessVector>& squaresSeen, ChessVector position) const;
    void getSquaresSeenByPiece(std::list<ChessVector>& squaresSeen, ChessVector position) const;
    void addMovesForPiece(std::list<Move>& moves, ChessVector position);
    void getMovesForPiece(std::list<Move>& moves, ChessVector position);
    void getAllMoves(std::list<Move>& moves, Colour playerColour);

    void doMove(const Move& move);

private:
    Piece pieces[8][8]; // Row-major (Rank then file)

    bool enPassantFlag          = false;

    bool whiteLeftRookMoved     = false;
    bool whiteRightRookMoved    = false;
    bool whiteKingMoved         = false;

    bool blackLeftRookMoved     = false;
    bool blackRightRookMoved    = false;
    bool blackKingMoved         = false;

    ChessVector positionOfLastMove = ChessVector::INVALID;


    ChessVector whiteKingPos = ChessVector::INVALID;
    ChessVector blackKingPos = ChessVector::INVALID;

    bool checksCalculated = false;
    std::list<ChessVector> positionsCheckingWhite;
    std::list<ChessVector> positionsCheckingBlack;

    void calculateChecks(Colour kingColour);

    void addSquaresSeenByPawn(std::list<ChessVector>& squaresSeen, ChessVector position) const;
    void addSquaresSeenByBishop(std::list<ChessVector>& squaresSeen, ChessVector position) const;
    void addSquaresSeenByKnight(std::list<ChessVector>& squaresSeen, ChessVector position) const;
    void addSquaresSeenByRook(std::list<ChessVector>& squaresSeen, ChessVector position) const;
    void addSquaresSeenByQueen(std::list<ChessVector>& squaresSeen, ChessVector position) const;
    void addSquaresSeenByKing(std::list<ChessVector>& squaresSeen, ChessVector position) const;

    void filterEndSquaresByCheckRules(std::list<ChessVector>& endSquares, ChessVector startPosition);
    void filterEndSquaresByAvailability(std::list<ChessVector>& endSquares, ChessVector startPosition) const;
    
    void addPawnMoves(std::list<Move>& moves, ChessVector position);
    void addBishopMoves(std::list<Move>& moves, ChessVector position);
    void addKnightMoves(std::list<Move>& moves, ChessVector position);
    void addRookMoves(std::list<Move>& moves, ChessVector position);
    void addQueenMoves(std::list<Move>& moves, ChessVector position);
    void addKingMoves(std::list<Move>& moves, ChessVector position);
};