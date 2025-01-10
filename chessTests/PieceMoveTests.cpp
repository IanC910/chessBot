
#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PieceMoveTests {

    TEST_CLASS(PieceMoveTests) {

        TEST_METHOD(pawnMovesTest) {
            Board board;
            std::list<Move> moves;

            ChessVector whitePawnPos(3, 6);
            Piece whitePawn(WHITE, PAWN);

            // pawn is the only piece on the board.
            // Only 1 legal move: straight forward
            board.setPiece(whitePawnPos, whitePawn);
            board.getMoves(moves, whitePawnPos);
            Assert::IsTrue(1 == moves.size());

            // Blocking piece of opposite colour
            // No legal moves for the pawn
            board.setPiece(4, 6, Piece(BLACK, BISHOP));
            board.getMoves(moves, whitePawnPos);
            Assert::IsTrue(0 == moves.size());

            // Blocking piece of same colour
            // No legal moves for the pawn
            board.setPiece(4, 6, Piece(WHITE, BISHOP));
            board.getMoves(moves, whitePawnPos);
            Assert::IsTrue(0 == moves.size());

            // Blocking piece of same colour, black pawn to the forward right
            // 1 legal move to take the black pawn
            board.setPiece(4, 5, Piece(BLACK, PAWN));
            board.getMoves(moves, whitePawnPos);
            Assert::IsTrue(1 == moves.size());

            // Additional black piece to the forward left
            // 2 legal moves to take either black piece
            board.setPiece(4, 7, Piece(BLACK, KNIGHT));
            board.getMoves(moves, whitePawnPos);
            Assert::IsTrue(2 == moves.size());

            // Remove blocker of same colour
            // 3 legal moves: take either black piece or straight forward
            board.setPiece(4, 6, Piece::NO_PIECE);
            board.getMoves(moves, whitePawnPos);
            Assert::IsTrue(3 == moves.size());

            // Pawn is pinned by queen of opposite colour
            // 1 legal move to take the queen
            board.clear();
            board.setPiece(4, 4, whitePawn);
            board.setPiece(3, 3, Piece(WHITE, KING));
            board.setPiece(5, 5, Piece(BLACK, QUEEN));
            board.getMoves(moves, ChessVector(4, 4));
            Assert::IsTrue(1 == moves.size());

            // 2 moves if self check filter is off
            board.getMoves(moves, ChessVector(4, 4), false);
            Assert::IsTrue(2 == moves.size());

            // Pawn is pinned by queen of opposite colour
            // 0 legal moves, queen is not takeable
            board.clear();
            board.setPiece(3, 3, Piece(WHITE, KING));
            board.setPiece(3, 4, whitePawn);
            board.setPiece(3, 5, Piece(BLACK, QUEEN));
            board.getMoves(moves, ChessVector(3, 4));
            Assert::IsTrue(0 == moves.size());

            // 1 move if self check filter is off
            board.getMoves(moves, ChessVector(3, 4), false);
            Assert::IsTrue(1 == moves.size());
        }
    };
}