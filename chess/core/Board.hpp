
#pragma once

#include <string>
#include <list>

#include "Move.hpp"
#include "Vector.hpp"
#include "Piece.hpp"

namespace Chess {

    class Board {
    public:
        Board();
        Board(const Board& board);

        bool equals(const Board& board) const;
        bool operator==(const Board& board) const;
        bool operator!=(const Board& board) const;
        std::string toString() const;

        Piece getPiece(char rank, char file) const;
        Piece getPiece(Vector position) const;
        void setPiece(char rank, char file, const Piece& piece);
        void setPiece(Vector position, const Piece& piece);

        void clear();

        void reset();

        Vector getKingPos(Colour colour) const;
        Vector getPinDirection(Vector position) const;
        bool isPiecePinned(Vector position) const;
        int getNumChecks(Colour kingColour);
        const std::list<Vector>* getPositionsCheckingKing(Colour kingColour);
        bool isKingChecked(Colour kingColour);
        void clearCalculatedChecks();
        bool getEnPassantFlag() const;

        void addSquaresSeenByPiece(std::list<Vector>& squaresSeen, Vector position) const;
        void getSquaresSeenByPiece(std::list<Vector>& squaresSeen, Vector position) const;
        void addMovesForPiece(std::list<Move>& moves, Vector position);
        void getMovesForPiece(std::list<Move>& moves, Vector position);
        void getAllMoves(std::list<Move>& moves, Colour playerColour);

        void doMove(const Move& move);

        int getMaterialValue();

    private:
        Piece pieces[8][8]; // Row-major (Rank then file)

        Vector positionOfLastMove = Vector::INVALID;
        bool enPassantFlag          = false;

        bool whiteCanShortCastle    = false;
        bool whiteCanLongCastle     = false;

        bool blackCanShortCastle    = false;
        bool blackCanLongCastle     = false;

        Vector whiteKingPos = Vector::INVALID;
        Vector blackKingPos = Vector::INVALID;

        Colour colourOfCalculatedChecks = NO_COLOUR;
        std::list<Vector> positionsCheckingKing;

        void calculateChecks(Colour kingColour);

        void addSquaresSeenByPawn(std::list<Vector>& squaresSeen, Vector position) const;
        void addSquaresSeenByBishop(std::list<Vector>& squaresSeen, Vector position) const;
        void addSquaresSeenByKnight(std::list<Vector>& squaresSeen, Vector position) const;
        void addSquaresSeenByRook(std::list<Vector>& squaresSeen, Vector position) const;
        void addSquaresSeenByQueen(std::list<Vector>& squaresSeen, Vector position) const;
        void addSquaresSeenByKing(std::list<Vector>& squaresSeen, Vector position) const;

        void filterEndSquaresByCheckRules(std::list<Vector>& endSquares, Vector startPosition);
        void filterEndSquaresByAvailability(std::list<Vector>& endSquares, Vector startPosition) const;
    
        void addPawnMoves(std::list<Move>& moves, Vector position);
        void addBishopMoves(std::list<Move>& moves, Vector position);
        void addKnightMoves(std::list<Move>& moves, Vector position);
        void addRookMoves(std::list<Move>& moves, Vector position);
        void addQueenMoves(std::list<Move>& moves, Vector position);
        void addKingMoves(std::list<Move>& moves, Vector position);
    };
}