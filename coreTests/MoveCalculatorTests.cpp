
#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Chess;

namespace MoveCalculatorTests {

    TEST_CLASS(PinDirectionTests) {

        TEST_METHOD(pinDirectionTest) {
            // Diagonal pin line
            Board board;
            MoveCalculator moveCalculator;

            board.setPiece(0, 0, Piece(WHITE, KING));
            board.setPiece(5, 5, Piece(BLACK, BISHOP));
            board.setPiece(1, 1, Piece(WHITE, PAWN));
            moveCalculator.setBoard(board);
            Assert::IsTrue(
                moveCalculator.getPinDirection(Vector(1, 1))
                .equals(Vector(1, 1))
            );

            // Horizontal pin line
            board.clear();
            board.setPiece(7, 7, Piece(BLACK, KING));
            board.setPiece(7, 0, Piece(WHITE, ROOK));
            board.setPiece(7, 6, Piece(BLACK, ROOK));
            moveCalculator.setBoard(board);
            Assert::IsTrue(
                moveCalculator.getPinDirection(Vector(7, 6))
                .equals(Vector(0, -1))
            );

            // Vertical pin line
            // Multiple defenders, all of kings colour
            // One defender moves out of pin line, does not check own king
            board.clear();
            board.setPiece(0, 5, Piece(WHITE, KING));
            board.setPiece(1, 5, Piece(WHITE, KNIGHT));
            board.setPiece(7, 5, Piece(BLACK, QUEEN));
            board.setPiece(5, 5, Piece(WHITE, QUEEN));
            moveCalculator.setBoard(board);
            Assert::IsTrue(
                moveCalculator.getPinDirection(Vector(5, 5))
                .equals(Vector(0, 0))
            );

            // Vertical pin line
            // Multiple defenders, not all of kings colour
            // One defender moves out of pin line, does not check own king
            board.clear();
            board.setPiece(0, 5, Piece(WHITE, KING));
            board.setPiece(1, 5, Piece(BLACK, KNIGHT));
            board.setPiece(7, 5, Piece(BLACK, QUEEN));
            board.setPiece(5, 5, Piece(WHITE, QUEEN));
            moveCalculator.setBoard(board);
            Assert::IsTrue(
                moveCalculator.getPinDirection(Vector(5, 5))
                .equals(Vector(0, 0))
            );

            // Diagonal pin line
            // No Attacker, so move does not check own king
            board.clear();
            board.setPiece(4, 5, Piece(WHITE, KING));
            board.setPiece(6, 3, Piece(WHITE, KNIGHT));
            moveCalculator.setBoard(board);
            Assert::IsTrue(
                moveCalculator.getPinDirection(Vector(6, 3))
                .equals(Vector(0, 0))
            );

            // King, same colour pawn, and opposite rook are on the same diagonal
            // Rook doesn't attack diagonally, pawn is not pinned
            board.clear();
            board.setPiece(0, 0, Piece(WHITE, KING));
            board.setPiece(1, 1, Piece(WHITE, PAWN));
            board.setPiece(2, 2, Piece(BLACK, ROOK));
            moveCalculator.setBoard(board);
            Assert::IsTrue(
                moveCalculator.getPinDirection(Vector(1, 1))
                .equals(Vector(0, 0))
            );
        }
    };

    TEST_CLASS(SquaresSeenTests) {

        TEST_METHOD(getSquaresSeenByPawnTest) {
            Board board;
            std::list<Vector> squaresSeen;
            MoveCalculator moveCalculator;

            // pawn is the only piece on the board.
            // Only 1 legal move: straight forward
            board.setPiece(3, 6, Piece(WHITE, PAWN));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(3, 6));
            Assert::IsTrue(2 == squaresSeen.size());

            // Opposite color pawn at the diagonal
            // Number of targeted squares for original pawn doesn't change
            board.setPiece(4, 7, Piece(BLACK, PAWN));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(3, 6));
            Assert::IsTrue(2 == squaresSeen.size());

            // Number of targeted squares for black pawn is 1 because on the edge of the board
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(4, 7));
            Assert::IsTrue(1 == squaresSeen.size());

            // Same color pawn at the diagonal
            // Number of targed squares for original pawn doesn't change
            board.setPiece(4, 7, Piece(WHITE, PAWN));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(3, 6));
            Assert::IsTrue(2 == squaresSeen.size());

            // Number of targeted squares for new pawn is 1 because on the edge of the board
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(4, 7));
            Assert::IsTrue(1 == squaresSeen.size());
        }

        TEST_METHOD(getSquaresSeenByBishopTest) {
            Board board;
            MoveCalculator moveCalculator;
            std::list<Vector> squaresSeen;

            // Only bishop is on the board
            // No restrictions on targeted squares besides board edges
            board.setPiece(0, 0, Piece(BLACK, BISHOP));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(0, 0));
            Assert::IsTrue(7 == squaresSeen.size());

            board.clear();
            board.setPiece(4, 4, Piece(WHITE, BISHOP));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(4, 4));
            Assert::IsTrue(13 == squaresSeen.size());

            // A piece of same colour blocks a path
            // Number of targeted squares reduces
            board.setPiece(3, 5, Piece(WHITE, PAWN));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(4, 4));
            Assert::IsTrue(11 == squaresSeen.size());

            // A piece of opposite colour blocks another path
            // Number of targeted squares reduces
            board.setPiece(2, 2, Piece(BLACK, QUEEN));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(4, 4));
            Assert::IsTrue(9 == squaresSeen.size());
        }

        TEST_METHOD(getSquaresSeenByKnightTest) {
            Board board;
            MoveCalculator moveCalculator;
            std::list<Vector> squaresSeen;

            // Knight in centre of board
            // Full range of motion
            board.setPiece(3, 3, Piece(BLACK, KNIGHT));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(3, 3));
            Assert::IsTrue(8 == squaresSeen.size());

            // Knight on side of board
            // Half range of motion
            board.setPiece(0, 2, Piece(BLACK, KNIGHT));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(0, 2));
            Assert::IsTrue(4 == squaresSeen.size());

            // Knight in corner of board
            // Quarter of range of motion
            board.setPiece(0, 0, Piece(WHITE, KNIGHT));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(0, 0));
            Assert::IsTrue(2 == squaresSeen.size());
        }

        TEST_METHOD(getSquaresSeenByRookTest) {
            Board board;
            MoveCalculator moveCalculator;
            std::list<Vector> squaresSeen;

            // Rook only piece on board
            // Full range of motion regardless of position
            board.setPiece(0, 0, Piece(WHITE, ROOK));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(0, 0));
            Assert::IsTrue(14 == squaresSeen.size());

            board.setPiece(4, 5, Piece(BLACK, ROOK));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(4, 5));
            Assert::IsTrue(14 == squaresSeen.size());

            // Piece of opposite colour blocks path
            board.setPiece(1, 5, Piece(WHITE, PAWN));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(4, 5));
            Assert::IsTrue(13 == squaresSeen.size());
        }

        TEST_METHOD(getSquaresSeenByQueenTest) {
            Board board;
            MoveCalculator moveCalculator;
            std::list<Vector> squaresSeen;

            // Queen in centre of board, only piece
            // Full range of motion
            board.setPiece(3, 3, Piece(WHITE, QUEEN));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(3, 3));
            Assert::IsTrue(27 == squaresSeen.size());

            board.clear();
            board.setPiece(0, 0, Piece(WHITE, QUEEN));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(0, 0));
            Assert::IsTrue(21 == squaresSeen.size());

            board.setPiece(1, 1, Piece(WHITE, KING));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(0, 0));
            Assert::IsTrue(15 == squaresSeen.size());

            board.setPiece(0, 1, Piece(WHITE, ROOK));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(squaresSeen, Vector(0, 0));
            Assert::IsTrue(9 == squaresSeen.size());
        }

        TEST_METHOD(getSquaresSeenByKingTest) {
            Board board;
            MoveCalculator moveCalculator;
            std::list<Vector> targetedSqaures;

            // King in centre of board
            // Full range of motion
            board.setPiece(3, 3, Piece(WHITE, KING));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(targetedSqaures, Vector(3, 3));
            Assert::IsTrue(8 == targetedSqaures.size());

            // King on side of board
            // Half range of motion
            board.setPiece(2, 7, Piece(WHITE, KING));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(targetedSqaures, Vector(2, 7));
            Assert::IsTrue(5 == targetedSqaures.size());

            // King in corner
            // Quarter range of motion
            board.setPiece(7, 0, Piece(BLACK, KING));
            moveCalculator.setBoard(board);
            moveCalculator.getSquaresSeenByPiece(targetedSqaures, Vector(7, 0));
            Assert::IsTrue(3 == targetedSqaures.size());
        }
        TEST_METHOD(getNumChecksTest) {
            Board board;
            MoveCalculator moveCalculator;

            board.setPiece(0, 0, Piece(WHITE, KING));
            moveCalculator.setBoard(board);
            Assert::IsTrue(0 == moveCalculator.getNumChecks(WHITE));
            Assert::IsTrue(0 == moveCalculator.getNumChecks(BLACK));

            board.setPiece(4, 4, Piece(WHITE, BISHOP));
            moveCalculator.setBoard(board);
            Assert::IsTrue(0 == moveCalculator.getNumChecks(WHITE));

            board.setPiece(4, 4, Piece(BLACK, BISHOP));
            moveCalculator.setBoard(board);
            Assert::IsTrue(1 == moveCalculator.getNumChecks(WHITE));

            board.setPiece(3, 3, Piece(BLACK, KNIGHT));
            moveCalculator.setBoard(board);
            Assert::IsTrue(0 == moveCalculator.getNumChecks(WHITE));

            board.setPiece(2, 1, Piece(BLACK, KNIGHT));
            moveCalculator.setBoard(board);
            Assert::IsTrue(1 == moveCalculator.getNumChecks(WHITE));

            board.setPiece(3, 3, Piece(BLACK, QUEEN));
            moveCalculator.setBoard(board);
            Assert::IsTrue(2 == moveCalculator.getNumChecks(WHITE));

            board.setPiece(3, 3, Piece::NO_PIECE);
            moveCalculator.setBoard(board);
            Assert::IsTrue(2 == moveCalculator.getNumChecks(WHITE));

            board.setPiece(3, 3, Piece(WHITE, PAWN));
            moveCalculator.setBoard(board);
            Assert::IsTrue(1 == moveCalculator.getNumChecks(WHITE));

            board.setPiece(1, 1, Piece(BLACK, PAWN));
            moveCalculator.setBoard(board);
            Assert::IsTrue(2 == moveCalculator.getNumChecks(WHITE));
        }
    };

    TEST_CLASS(MoveAvailabilityTests) {

        TEST_METHOD(getPawnMovesTest) {
            Board board;
            MoveCalculator moveCalculator;
            std::list<Move> moves;

            Vector whitePawnPos(3, 6);
            Piece whitePawn(WHITE, PAWN);

            // pawn is the only piece on the board.
            // Only 1 legal move: straight forward
            board.setPiece(whitePawnPos, whitePawn);
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, whitePawnPos);
            Assert::IsTrue(1 == moves.size());

            // Blocking piece of opposite colour
            // No legal moves for the pawn
            board.setPiece(4, 6, Piece(BLACK, BISHOP));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, whitePawnPos);
            Assert::IsTrue(0 == moves.size());

            // Blocking piece of same colour
            // No legal moves for the pawn
            board.setPiece(4, 6, Piece(WHITE, BISHOP));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, whitePawnPos);
            Assert::IsTrue(0 == moves.size());

            // Blocking piece of same colour, black pawn to the forward right
            // 1 legal move to take the black pawn
            board.setPiece(4, 5, Piece(BLACK, PAWN));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, whitePawnPos);
            Assert::IsTrue(1 == moves.size());

            // Additional black piece to the forward left
            // 2 legal moves to take either black piece
            board.setPiece(4, 7, Piece(BLACK, KNIGHT));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, whitePawnPos);
            Assert::IsTrue(2 == moves.size());

            // Remove blocker of same colour
            // 3 legal moves: take either black piece or straight forward
            board.setPiece(4, 6, Piece::NO_PIECE);
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, whitePawnPos);
            Assert::IsTrue(3 == moves.size());

            // Pawn is pinned by queen of opposite colour
            // 1 legal move to take the queen
            board.clear();
            board.setPiece(4, 4, whitePawn);
            board.setPiece(3, 3, Piece(WHITE, KING));
            board.setPiece(5, 5, Piece(BLACK, QUEEN));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 4, 4 });
            Assert::IsTrue(1 == moves.size());

            // Pawn is pinned by queen of opposite colour
            // 0 legal moves, queen is not takeable
            board.clear();
            board.setPiece(3, 3, Piece(WHITE, KING));
            board.setPiece(3, 4, whitePawn);
            board.setPiece(3, 5, Piece(BLACK, QUEEN));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 4 });
            Assert::IsTrue(0 == moves.size());

            // King is checked
            // Only move is to block check
            board.clear();
            board.setPiece(1, 2, Piece(BLACK, KING));
            board.setPiece(1, 6, Piece(WHITE, ROOK));
            board.setPiece(2, 3, Piece(BLACK, PAWN));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 2, 3 });
            Assert::IsTrue(1 == moves.size());

            // Same conditions but now there is another option
            board.clear();
            board.setPiece(1, 2, Piece(BLACK, KING));
            board.setPiece(4, 5, Piece(WHITE, BISHOP));
            board.setPiece(2, 4, Piece(WHITE, BISHOP));
            board.setPiece(3, 3, Piece(BLACK, PAWN));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(1 == moves.size());
        }

        TEST_METHOD(getBishopMovesTest) {
            Board board;
            MoveCalculator moveCalculator;
            std::list<Move> moves;

            board.setPiece(0, 0, Piece(WHITE, BISHOP));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 0, 0 });
            Assert::IsTrue(7 == moves.size());

            board.setPiece(1, 1, Piece(WHITE, PAWN));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 0, 0 });
            Assert::IsTrue(0 == moves.size());

            board.setPiece(1, 1, Piece(BLACK, PAWN));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 0, 0 });
            Assert::IsTrue(1 == moves.size());

            board.clear();
            board.setPiece(3, 3, Piece(WHITE, BISHOP));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(13 == moves.size());

            board.setPiece(1, 1, Piece(BLACK, QUEEN));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(12 == moves.size());

            board.setPiece(2, 2, Piece(WHITE, QUEEN));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(10 == moves.size());

            // Bishop is pinned but on same diagonal as pinner
            // Can take or go back 1
            board.clear();
            board.setPiece(4, 5, Piece(WHITE, KING));
            board.setPiece(2, 3, Piece(WHITE, BISHOP));
            board.setPiece(1, 2, Piece(BLACK, QUEEN));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 2, 3 });
            Assert::IsTrue(2 == moves.size());

            // Bishop is not pinned, but king is checked
            // Only move is to block check
            board.clear();
            board.setPiece(4, 5, Piece(WHITE, KING));
            board.setPiece(1, 4, Piece(WHITE, BISHOP));
            board.setPiece(1, 2, Piece(BLACK, QUEEN));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 1, 4 });
            Assert::IsTrue(1 == moves.size());

            // Bishop not pinned, king is checked
            // Bishop can only make it behind the king, can't block
            // No moves
            board.clear();
            board.setPiece(4, 5, Piece(WHITE, KING));
            board.setPiece(1, 2, Piece(BLACK, QUEEN));
            board.setPiece(4, 7, Piece(WHITE, BISHOP));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 4, 7 });
            Assert::IsTrue(0 == moves.size());

            // Bishop not pinned, king is checked
            // Bishop can only make it behind the checker, can't block
            // No moves
            board.clear();
            board.setPiece(4, 5, Piece(WHITE, KING));
            board.setPiece(1, 2, Piece(BLACK, QUEEN));
            board.setPiece(1, 0, Piece(WHITE, BISHOP));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 1, 0 });
            Assert::IsTrue(0 == moves.size());
        }

        TEST_METHOD(getKnightMovesTest) {
            Board board;
            MoveCalculator moveCalculator;
            std::list<Move> moves;

            // Knight in centre of board, only piece
            // Full range of motion
            board.setPiece(3, 3, Piece(WHITE, KNIGHT));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(8 == moves.size());

            // Same colour pawn in one end square
            // Can't move there
            board.setPiece(2, 5, Piece(WHITE, PAWN));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(7 == moves.size());

            // Opposute colour pawn in another end square
            // No effect
            board.setPiece(4, 5, Piece(BLACK, PAWN));
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(7 == moves.size());

            // Knight pinned, no moves
            board.clear();
            board.setPiece(3, 3, Piece(BLACK, KNIGHT));
            board.setPiece(2, 2, Piece(BLACK, KING));
            board.setPiece(4, 4, Piece(WHITE, BISHOP));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(0 == moves.size());

            // King checked
            // Only move is to take it
            board.clear();
            board.setPiece(4, 2, Piece(WHITE, KING));
            board.setPiece(4, 4, Piece(BLACK, ROOK));
            board.setPiece(5, 6, Piece(WHITE, KNIGHT));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 5, 6 });
            Assert::IsTrue(1 == moves.size());

            // Same as above but now knight can also block
            board.clear();
            board.setPiece(4, 2, Piece(WHITE, KING));
            board.setPiece(4, 5, Piece(BLACK, ROOK));
            board.setPiece(6, 4, Piece(WHITE, KNIGHT));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 6, 4 });
            Assert::IsTrue(2 == moves.size());
        }

        TEST_METHOD(getRookMovesTest) {
            Board board;
            MoveCalculator moveCalculator;
            std::list<Move> moves;

            // Rook in centre of board, only piece
            // Full range of motion
            board.setPiece(3, 3, Piece(WHITE, ROOK));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(14 == moves.size());

            // Opposite colour piece blocks a path
            board.setPiece(6, 3, Piece(BLACK, PAWN));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(13 == moves.size());

            // Same colour piece blocks another path
            board.setPiece(3, 5, Piece(WHITE, KING));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(10 == moves.size());

            // Rook is pinned diagonally, no moves
            board.clear();
            board.setPiece(3, 3, Piece(WHITE, KING));
            board.setPiece(5, 5, Piece(BLACK, BISHOP));
            board.setPiece(4, 4, Piece(WHITE, ROOK));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 4, 4 });
            Assert::IsTrue(0 == moves.size());

            // Rook is pinned horizontally
            // Some moves, including taking checking piece
            board.clear();
            board.setPiece(3, 3, Piece(WHITE, KING));
            board.setPiece(3, 7, Piece(BLACK, QUEEN));
            board.setPiece(3, 4, Piece(WHITE, ROOK));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 4 });
            Assert::IsTrue(3 == moves.size());

            // King is checked, rook can block
            board.clear();
            board.setPiece(3, 3, Piece(WHITE, KING));
            board.setPiece(3, 7, Piece(BLACK, QUEEN));
            board.setPiece(5, 5, Piece(WHITE, ROOK));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 5, 5 });
            Assert::IsTrue(1 == moves.size());

            // King is checked, rook can't block as it's behind the king
            board.clear();
            board.setPiece(3, 3, Piece(WHITE, KING));
            board.setPiece(3, 7, Piece(BLACK, QUEEN));
            board.setPiece(5, 2, Piece(WHITE, ROOK));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 5, 2 });
            Assert::IsTrue(0 == moves.size());

            // King is checked, only move is to take checker
            board.clear();
            board.setPiece(3, 3, Piece(WHITE, KING));
            board.setPiece(3, 7, Piece(BLACK, QUEEN));
            board.setPiece(5, 7, Piece(WHITE, ROOK));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 5, 7 });
            Assert::IsTrue(1 == moves.size());
        }

        TEST_METHOD(getQueenMovesTest) {
            Board board;
            MoveCalculator moveCalculator;
            std::list<Move> moves;

            // Queen in centre of board, only piece
            // Full range of motion
            board.setPiece(3, 3, Piece(WHITE, QUEEN));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(27 == moves.size());

            // Queen is forked by kngiht, no moves
            board.setPiece(3, 3, Piece(WHITE, QUEEN));
            board.setPiece(3, 5, Piece(WHITE, KING));
            board.setPiece(5, 4, Piece(BLACK, KNIGHT));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(0 == moves.size());
        }

        TEST_METHOD(getKingMovesTest) {
            Board board;
            MoveCalculator moveCalculator;
            std::list<Move> moves;

            // King in centre of board, only piece
            // Full range of motion
            board.setPiece(3, 3, Piece(WHITE, KING));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(8 == moves.size());

            // Some same colour pieces next to king, restricting movement
            board.setPiece(2, 3, Piece(WHITE, PAWN));
            board.setPiece(3, 4, Piece(WHITE, QUEEN));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(6 == moves.size());

            // Some opposite colour pawns next to king
            // one is checking king
            // Valid moves to take either of them
            board.setPiece(2, 4, Piece(BLACK, PAWN));
            board.setPiece(4, 2, Piece(BLACK, PAWN));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(6 == moves.size());

            // One of the opposite pawns is protected
            // Can no longer take it
            board.setPiece(5, 2, Piece(BLACK, ROOK));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(5 == moves.size());

            // Opposite colour bishop protects one of previously available squares
            board.setPiece(4, 0, Piece(BLACK, BISHOP));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(4 == moves.size());

            // Opposite colour queen protects more squares
            board.setPiece(4, 6, Piece(BLACK, QUEEN));
            board.setPiece(5, 2, Piece::NO_PIECE);
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(1 == moves.size());

            // Opposte colour bishop protects the last available square
            board.setPiece(5, 0, Piece(BLACK, BISHOP));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(0 == moves.size());

            // All available squares are checked, only move is to take a checker
            board.setPiece(2, 2, Piece(BLACK, BISHOP));
            board.setPiece(4, 0, Piece::NO_PIECE);
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 3, 3 });
            Assert::IsTrue(1 == moves.size());
        }

        TEST_METHOD(startingMovesTest) {
            Board board;
            MoveCalculator moveCalculator;
            std::list<Move> moves;

            board.reset();
            moveCalculator.setBoard(board);
            moveCalculator.getAllMoves(moves, WHITE);
            Assert::IsTrue(20 == moves.size());
            moveCalculator.getAllMoves(moves, BLACK);
            Assert::IsTrue(20 == moves.size());
        }

        TEST_METHOD(enPassantTest) {
            Board board;
            MoveCalculator moveCalculator;
            std::list<Move> moves;

            board.setPiece(4, 5, Piece(WHITE, PAWN));
            board.setPiece(6, 4, Piece(BLACK, PAWN));
            moveCalculator.setBoard(board);

            Assert::IsFalse(board.wasLastMoveDoublePawn());
            moveCalculator.getMovesForPiece(moves, { 4, 5 });
            Assert::IsTrue(1 == moves.size());
            moveCalculator.getMovesForPiece(moves, { 6, 4 });
            Assert::IsTrue(2 == moves.size());

            // Check that the double pawn move is available for black
            Move doublePawnMove({ 6, 4 }, { 4, 4 }, Piece(BLACK, PAWN));
            bool movesContainsDoublePawnMove = false;
            for (Move& move : moves) {
                if (move == doublePawnMove) {
                    movesContainsDoublePawnMove = true;
                }
            }
            Assert::IsTrue(movesContainsDoublePawnMove);

            // Do double pawn move, setting up conditions for en passant
            board.doMove(doublePawnMove);
            moveCalculator.setBoard(board);
            Assert::IsTrue(board.wasLastMoveDoublePawn());
            moveCalculator.getMovesForPiece(moves, { 4, 5 });
            Assert::IsTrue(2 == moves.size());

            // Check that the en passant move is available for white
            Move enPassantMove({ 4, 5 }, { 5, 4 }, Piece(WHITE, PAWN), EN_PASSANT);
            bool movesContainsEnPassantMove = false;
            for (Move& move : moves) {
                if (move == enPassantMove) {
                    movesContainsEnPassantMove = true;
                }
            }
            Assert::IsTrue(movesContainsEnPassantMove);

            // Make the white pawn pinned. Check that the en passant move goes away
            board.setPiece(0, 5, Piece(WHITE, KING));
            board.setPiece(7, 5, Piece(BLACK, ROOK));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 4, 5 });
            Assert::IsTrue(1 == moves.size());

            // Do en passant (despite being illegal because the white pawn is pinned)
            // Check that the black pawn is removed from the board
            board.doMove(enPassantMove);
            Assert::IsTrue(board.getPiece(4, 4) == Piece::NO_PIECE);
        }

        TEST_METHOD(castleAvailabilityTest) {
            Board board;
            MoveCalculator moveCalculator;
            std::list<Move> moves;

            board.reset();
            for (char f = 0; f < 8; f++) {
                board.setPiece(1, f, Piece::NO_PIECE);
                board.setPiece(6, f, Piece::NO_PIECE);
            }
            for (char f = 1; f <= 3; f++) {
                board.setPiece(0, f, Piece::NO_PIECE);
                board.setPiece(7, f, Piece::NO_PIECE);
            }
            for (char f = 5; f <= 6; f++) {
                board.setPiece(0, f, Piece::NO_PIECE);
                board.setPiece(7, f, Piece::NO_PIECE);
            }


            // Check that white king can castle in both directions
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 0, 4 });
            Assert::IsTrue(7 == moves.size());

            // Put piece in the way of shortcastling, king can only long castle
            board.setPiece(0, 5, Piece(BLACK, BISHOP));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 0, 4 });
            Assert::IsTrue(5 == moves.size());

            // Have an enemy piece be able to see a square needed for castling
            board.setPiece(0, 5, Piece::NO_PIECE);
            board.setPiece(6, 0, Piece(BLACK, BISHOP));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 0, 4 });
            Assert::IsTrue(5 == moves.size());

            // Block the attacking piece
            board.setPiece(5, 1, Piece(WHITE, PAWN));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 0, 4 });
            Assert::IsTrue(7 == moves.size());

            board.setPiece(6, 0, Piece::NO_PIECE);
            board.setPiece(5, 1, Piece::NO_PIECE);

            // Move long rook. white king can only short castle now
            board.doMove(Move({ 0, 0 }, { 0, 1 }, Piece(WHITE, ROOK)));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 0, 4 });
            Assert::IsTrue(6 == moves.size());

            // Move short rook. White king cannot castle now
            board.doMove(Move({ 0, 7 }, { 1, 7 }, Piece(WHITE, ROOK)));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 0, 4 });
            Assert::IsTrue(5 == moves.size());

            // Black king can still castle in both directions
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 7, 4 });
            Assert::IsTrue(7 == moves.size());

            // Black king moves, can no longer castle
            board.doMove(Move({ 7, 4 }, { 7, 3 }, Piece(BLACK, KING)));
            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 7, 3 });
            Assert::IsTrue(5 == moves.size());
        }

        TEST_METHOD(castleMoveTest) {
            Board board;
            MoveCalculator moveCalculator;
            std::list<Move> moves;

            board.reset();
            for (char f = 0; f < 8; f++) {
                board.setPiece(1, f, Piece::NO_PIECE);
                board.setPiece(6, f, Piece::NO_PIECE);
            }
            for (char f = 1; f <= 3; f++) {
                board.setPiece(0, f, Piece::NO_PIECE);
                board.setPiece(7, f, Piece::NO_PIECE);
            }
            for (char f = 5; f <= 6; f++) {
                board.setPiece(0, f, Piece::NO_PIECE);
                board.setPiece(7, f, Piece::NO_PIECE);
            }

            moveCalculator.setBoard(board);
            moveCalculator.getMovesForPiece(moves, { 0, 4 });
            Assert::IsTrue(7 == moves.size());

            for (Move& move : moves) {
                if (move.specialType == LONG_CASTLE) {
                    board.doMove(move);
                    break;
                }
            }

            Assert::IsTrue(board.getPiece(0, 2) == Piece(WHITE, KING));
            Assert::IsTrue(board.getPiece(0, 3) == Piece(WHITE, ROOK));
            Assert::IsTrue(board.getPiece(0, 4) == Piece::NO_PIECE);
            Assert::IsTrue(board.getPiece(0, 0) == Piece::NO_PIECE);
        }
    };
}