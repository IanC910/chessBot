
#pragma once

#include <list>

#include "Board.hpp"
#include "Vector.hpp"

namespace Chess {

    class BoardAnalyzer {
    public:
        BoardAnalyzer();
        BoardAnalyzer(const Board& board);

        void setBoard(const Board& board);

        void findKings();
        Vector getKingPos(Colour kingColour) const;

        Vector getPinDirection(Vector position) const;
        bool isPiecePinned(Vector position) const;

        int getNumChecks(Colour kingColour);
        const std::list<Vector>& getPositionsCheckingKing(Colour kingColour);
        bool isKingChecked(Colour kingColour);

        void addSquaresSeenByPiece(std::list<Vector>& squaresSeen, Vector position) const;
        void getSquaresSeenByPiece(std::list<Vector>& squaresSeen, Vector position) const;
        void addMovesForPiece(std::list<Move>& moves, Vector position);
        void getMovesForPiece(std::list<Move>& moves, Vector position);
        void getAllMoves(std::list<Move>& moves, Colour playerColour);

    private:
        Board board;

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

