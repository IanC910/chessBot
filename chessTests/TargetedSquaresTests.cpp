
#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TargetedSquaresTests {

    TEST_CLASS(TargetedSquaresTests) {

        TEST_METHOD(targetedSquaresByPawnTest) {
            Board board;
            std::list<ChessVector> targetedSquares;

            // pawn is the only piece on the board.
            // Only 1 legal move: straight forward
            board.setPiece(3, 6, Piece(WHITE, PAWN));
            board.getTargetedSquares(targetedSquares, ChessVector(3, 6));
            Assert::IsTrue(2 == targetedSquares.size());

            // Opposite color pawn at the diagonal
            // Number of targeted squares for original pawn doesn't change
            board.setPiece(4, 7, Piece(BLACK, PAWN));
            board.getTargetedSquares(targetedSquares, ChessVector(3, 6));
            Assert::IsTrue(2 == targetedSquares.size());

            // Number of targeted squares for black pawn is 1 because on the edge of the board
            board.getTargetedSquares(targetedSquares, ChessVector(4, 7));
            Assert::IsTrue(1 == targetedSquares.size());

            // Same color pawn at the diagonal
            // Number of targed squares for original pawn doesn't change
            board.setPiece(4, 7, Piece(WHITE, PAWN));
            board.getTargetedSquares(targetedSquares, ChessVector(3, 6));
            Assert::IsTrue(2 == targetedSquares.size());

            // Number of targeted squares for new pawn is 1 because on the edge of the board
            board.getTargetedSquares(targetedSquares, ChessVector(4, 7));
            Assert::IsTrue(1 == targetedSquares.size());
        }

        TEST_METHOD(targetedSquaresByBishopTest) {
            Board board;
            std::list<ChessVector> targetedSquares;

            // Only bishop is on the board
            // No restrictions on targeted squares besides board edges
            board.setPiece(0, 0, Piece(BLACK, BISHOP));
            board.getTargetedSquares(targetedSquares, ChessVector(0, 0));
            Assert::IsTrue(7 == targetedSquares.size());

            board.clear();
            board.setPiece(4, 4, Piece(WHITE, BISHOP));
            board.getTargetedSquares(targetedSquares, ChessVector(4, 4));
            Assert::IsTrue(13 == targetedSquares.size());

            // A piece of same colour blocks a path
            // Number of targeted squares reduces
            board.setPiece(3, 5, Piece(WHITE, PAWN));
            board.getTargetedSquares(targetedSquares, ChessVector(4, 4));
            Assert::IsTrue(11 == targetedSquares.size());

            // A piece of opposite colour blocks another path
            // Number of targeted squares reduces
            board.setPiece(2, 2, Piece(BLACK, QUEEN));
            board.getTargetedSquares(targetedSquares, ChessVector(4, 4));
            Assert::IsTrue(9 == targetedSquares.size());
        }

        TEST_METHOD(targetedSquaresByKnightTest) {
            Board board;
            std::list<ChessVector> targetedSquares;

            // Knight in centre of board
            // Full range of motion
            board.setPiece(3, 3, Piece(BLACK, KNIGHT));
            board.getTargetedSquares(targetedSquares, ChessVector(3, 3));
            Assert::IsTrue(8 == targetedSquares.size());

            // Knight on side of board
            // Half range of motion
            board.setPiece(0, 2, Piece(BLACK, KNIGHT));
            board.getTargetedSquares(targetedSquares, ChessVector(0, 2));
            Assert::IsTrue(4 == targetedSquares.size());

            // Knight in corner of board
            // Quarter of range of motion
            board.setPiece(0, 0, Piece(WHITE, KNIGHT));
            board.getTargetedSquares(targetedSquares, ChessVector(0, 0));
            Assert::IsTrue(2 == targetedSquares.size());
        }

        TEST_METHOD(targetedSquaresByRookTest) {
            Board board;
            std::list<ChessVector> targetedSquares;

            // Rook only piece on board
            // Full range of motion regardless of position
            board.setPiece(0, 0, Piece(WHITE, ROOK));
            board.getTargetedSquares(targetedSquares, ChessVector(0, 0));
            Assert::IsTrue(14 == targetedSquares.size());

            board.setPiece(4, 5, Piece(BLACK, ROOK));
            board.getTargetedSquares(targetedSquares, ChessVector(4, 5));
            Assert::IsTrue(14 == targetedSquares.size());

            // Piece of opposite colour blocks path
            board.setPiece(1, 5, Piece(WHITE, PAWN));
            board.getTargetedSquares(targetedSquares, ChessVector(4, 5));
            Assert::IsTrue(13 == targetedSquares.size());
        }

        TEST_METHOD(targetedSquaresByQueenTest) {
            Board board;
            std::list<ChessVector> targetedSquares;

            // Queen in centre of board, only piece
            // Full range of motion
            board.setPiece(3, 3, Piece(WHITE, QUEEN));
            board.getTargetedSquares(targetedSquares, ChessVector(3, 3));
            Assert::IsTrue(27 == targetedSquares.size());

            board.clear();
            board.setPiece(0, 0, Piece(WHITE, QUEEN));
            board.getTargetedSquares(targetedSquares, ChessVector(0, 0));
            Assert::IsTrue(21 == targetedSquares.size());

            board.setPiece(1, 1, Piece(WHITE, KING));
            board.getTargetedSquares(targetedSquares, ChessVector(0, 0));
            Assert::IsTrue(15 == targetedSquares.size());

            board.setPiece(0, 1, Piece(WHITE, ROOK));
            board.getTargetedSquares(targetedSquares, ChessVector(0, 0));
            Assert::IsTrue(9 == targetedSquares.size());
        }

        TEST_METHOD(targetedSquaresByKingTest) {
            Board board;
            std::list<ChessVector> targetedSqaures;

            // King in centre of board
            // Full range of motion
            board.setPiece(3, 3, Piece(WHITE, KING));
            board.getTargetedSquares(targetedSqaures, ChessVector(3, 3));
            Assert::IsTrue(8 == targetedSqaures.size());

            // King on side of board
            // Half range of motion
            board.setPiece(2, 7, Piece(WHITE, KING));
            board.getTargetedSquares(targetedSqaures, ChessVector(2, 7));
            Assert::IsTrue(5 == targetedSqaures.size());

            // King in corner
            // Quarter range of motion
            board.setPiece(7, 0, Piece(BLACK, KING));
            board.getTargetedSquares(targetedSqaures, ChessVector(7, 0));
            Assert::IsTrue(3 == targetedSqaures.size());
        }
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