
#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PieceMoveTests {

    TEST_CLASS(PieceMoveTests) {

        TEST_METHOD(getPawnMovesTest) {
            Board board;
            std::list<Move> moves;

            ChessVector whitePawnPos(3, 6);
            Piece whitePawn(WHITE, PAWN);

            // pawn is the only piece on the board.
            // Only 1 legal move: straight forward
            board.setPiece(whitePawnPos, whitePawn);
            board.getMovesForPiece(moves, whitePawnPos);
            Assert::IsTrue(1 == moves.size());

            // Blocking piece of opposite colour
            // No legal moves for the pawn
            board.setPiece(4, 6, Piece(BLACK, BISHOP));
            board.getMovesForPiece(moves, whitePawnPos);
            Assert::IsTrue(0 == moves.size());

            // Blocking piece of same colour
            // No legal moves for the pawn
            board.setPiece(4, 6, Piece(WHITE, BISHOP));
            board.getMovesForPiece(moves, whitePawnPos);
            Assert::IsTrue(0 == moves.size());

            // Blocking piece of same colour, black pawn to the forward right
            // 1 legal move to take the black pawn
            board.setPiece(4, 5, Piece(BLACK, PAWN));
            board.getMovesForPiece(moves, whitePawnPos);
            Assert::IsTrue(1 == moves.size());

            // Additional black piece to the forward left
            // 2 legal moves to take either black piece
            board.setPiece(4, 7, Piece(BLACK, KNIGHT));
            board.getMovesForPiece(moves, whitePawnPos);
            Assert::IsTrue(2 == moves.size());

            // Remove blocker of same colour
            // 3 legal moves: take either black piece or straight forward
            board.setPiece(4, 6, Piece::NO_PIECE);
            board.getMovesForPiece(moves, whitePawnPos);
            Assert::IsTrue(3 == moves.size());

            // Pawn is pinned by queen of opposite colour
            // 1 legal move to take the queen
            board.clear();
            board.setPiece(4, 4, whitePawn);
            board.setPiece(3, 3, Piece(WHITE, KING));
            board.setPiece(5, 5, Piece(BLACK, QUEEN));
            board.getMovesForPiece(moves, ChessVector(4, 4));
            Assert::IsTrue(1 == moves.size());

            // Pawn is pinned by queen of opposite colour
            // 0 legal moves, queen is not takeable
            board.clear();
            board.setPiece(3, 3, Piece(WHITE, KING));
            board.setPiece(3, 4, whitePawn);
            board.setPiece(3, 5, Piece(BLACK, QUEEN));
            board.getMovesForPiece(moves, ChessVector(3, 4));
            Assert::IsTrue(0 == moves.size());

            // King is checked
            // Only move is to block check
            board.clear();
            board.setPiece(1, 2, Piece(BLACK, KING));
            board.setPiece(1, 6, Piece(WHITE, ROOK));
            board.setPiece(2, 3, Piece(BLACK, PAWN));
            board.getMovesForPiece(moves, ChessVector(2, 3));
            Assert::IsTrue(1 == moves.size());

            // Same conditions but now there is another option
            board.clear();
            board.setPiece(1, 2, Piece(BLACK, KING));
            board.setPiece(4, 5, Piece(WHITE, BISHOP));
            board.setPiece(2, 4, Piece(WHITE, BISHOP));
            board.setPiece(3, 3, Piece(BLACK, PAWN));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(1 == moves.size());
        }

        TEST_METHOD(getBishopMovesTest) {
            Board board;
            std::list<Move> moves;

            board.setPiece(0, 0, Piece(WHITE, BISHOP));
            board.getMovesForPiece(moves, ChessVector(0, 0));
            Assert::IsTrue(7 == moves.size());

            board.setPiece(1, 1, Piece(WHITE, PAWN));
            board.getMovesForPiece(moves, ChessVector(0, 0));
            Assert::IsTrue(0 == moves.size());

            board.setPiece(1, 1, Piece(BLACK, PAWN));
            board.getMovesForPiece(moves, ChessVector(0, 0));
            Assert::IsTrue(1 == moves.size());

            board.clear();
            board.setPiece(3, 3, Piece(WHITE, BISHOP));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(13 == moves.size());

            board.setPiece(1, 1, Piece(BLACK, QUEEN));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(12 == moves.size());

            board.setPiece(2, 2, Piece(WHITE, QUEEN));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(10 == moves.size());

            // Bishop is pinned but on same diagonal as pinner
            // Can take or go back 1
            board.clear();
            board.setPiece(4, 5, Piece(WHITE, KING));
            board.setPiece(2, 3, Piece(WHITE, BISHOP));
            board.setPiece(1, 2, Piece(BLACK, QUEEN));
            board.getMovesForPiece(moves, ChessVector(2, 3));
            Assert::IsTrue(2 == moves.size());

            // Bishop is not pinned, but king is checked
            // Only move is to block check
            board.clear();
            board.setPiece(4, 5, Piece(WHITE, KING));
            board.setPiece(1, 4, Piece(WHITE, BISHOP));
            board.setPiece(1, 2, Piece(BLACK, QUEEN));
            board.getMovesForPiece(moves, ChessVector(1, 4));
            Assert::IsTrue(1 == moves.size());

            // Bishop not pinned, king is checked
            // Bishop can only make it behind the king, can't block
            // No moves
            board.clear();
            board.setPiece(4, 5, Piece(WHITE, KING));
            board.setPiece(1, 2, Piece(BLACK, QUEEN));
            board.setPiece(4, 7, Piece(WHITE, BISHOP));
            board.getMovesForPiece(moves, ChessVector(4, 7));
            Assert::IsTrue(0 == moves.size());

            // Bishop not pinned, king is checked
            // Bishop can only make it behind the checker, can't block
            // No moves
            board.clear();
            board.setPiece(4, 5, Piece(WHITE, KING));
            board.setPiece(1, 2, Piece(BLACK, QUEEN));
            board.setPiece(1, 0, Piece(WHITE, BISHOP));
            board.getMovesForPiece(moves, ChessVector(1, 0));
            Assert::IsTrue(0 == moves.size());
        }

        TEST_METHOD(getKnightMovesTest) {
            Board board;
            std::list<Move> moves;

            // Knight in centre of board, only piece
            // Full range of motion
            board.setPiece(3, 3, Piece(WHITE, KNIGHT));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(8 == moves.size());

            // Same colour pawn in one end square
            // Can't move there
            board.setPiece(2, 5, Piece(WHITE, PAWN));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(7 == moves.size());

            // Opposute colour pawn in another end square
            // No effect
            board.setPiece(4, 5, Piece(BLACK, PAWN));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(7 == moves.size());

            // Knight pinned, no moves
            board.clear();
            board.setPiece(3, 3, Piece(BLACK, KNIGHT));
            board.setPiece(2, 2, Piece(BLACK, KING));
            board.setPiece(4, 4, Piece(WHITE, BISHOP));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(0 == moves.size());

            // King checked
            // Only move is to take it
            board.clear();
            board.setPiece(4, 2, Piece(WHITE, KING));
            board.setPiece(4, 4, Piece(BLACK, ROOK));
            board.setPiece(5, 6, Piece(WHITE, KNIGHT));
            board.getMovesForPiece(moves, ChessVector(5, 6));
            Assert::IsTrue(1 == moves.size());

            // Same as above but now knight can also block
            board.clear();
            board.setPiece(4, 2, Piece(WHITE, KING));
            board.setPiece(4, 5, Piece(BLACK, ROOK));
            board.setPiece(6, 4, Piece(WHITE, KNIGHT));
            board.getMovesForPiece(moves, ChessVector(6, 4));
            Assert::IsTrue(2 == moves.size());
        }

        TEST_METHOD(getRookMovesTest) {
            Board board;
            std::list<Move> moves;

            // Rook in centre of board, only piece
            // Full range of motion
            board.setPiece(3, 3, Piece(WHITE, ROOK));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(14 == moves.size());

            // Opposite colour piece blocks a path
            board.setPiece(6, 3, Piece(BLACK, PAWN));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(13 == moves.size());

            // Same colour piece blocks another path
            board.setPiece(3, 5, Piece(WHITE, KING));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(10 == moves.size());

            // Rook is pinned diagonally, no moves
            board.clear();
            board.setPiece(3, 3, Piece(WHITE, KING));
            board.setPiece(5, 5, Piece(BLACK, BISHOP));
            board.setPiece(4, 4, Piece(WHITE, ROOK));
            board.getMovesForPiece(moves, ChessVector(4, 4));
            Assert::IsTrue(0 == moves.size());

            // Rook is pinned horizontally
            // Some moves, including taking checking piece
            board.clear();
            board.setPiece(3, 3, Piece(WHITE, KING));
            board.setPiece(3, 7, Piece(BLACK, QUEEN));
            board.setPiece(3, 4, Piece(WHITE, ROOK));
            board.getMovesForPiece(moves, ChessVector(3, 4));
            Assert::IsTrue(3 == moves.size());

            // King is checked, rook can block
            board.clear();
            board.setPiece(3, 3, Piece(WHITE, KING));
            board.setPiece(3, 7, Piece(BLACK, QUEEN));
            board.setPiece(5, 5, Piece(WHITE, ROOK));
            board.getMovesForPiece(moves, ChessVector(5, 5));
            Assert::IsTrue(1 == moves.size());

            // King is checked, rook can't block as it's behind the king
            board.clear();
            board.setPiece(3, 3, Piece(WHITE, KING));
            board.setPiece(3, 7, Piece(BLACK, QUEEN));
            board.setPiece(5, 2, Piece(WHITE, ROOK));
            board.getMovesForPiece(moves, ChessVector(5, 2));
            Assert::IsTrue(0 == moves.size());

            // King is checked, only move is to take checker
            board.clear();
            board.setPiece(3, 3, Piece(WHITE, KING));
            board.setPiece(3, 7, Piece(BLACK, QUEEN));
            board.setPiece(5, 7, Piece(WHITE, ROOK));
            board.getMovesForPiece(moves, ChessVector(5, 7));
            Assert::IsTrue(1 == moves.size());
        }

        TEST_METHOD(getQueenMovesTest) {
            Board board;
            std::list<Move> moves;

            // Queen in centre of board, only piece
            // Full range of motion
            board.setPiece(3, 3, Piece(WHITE, QUEEN));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(27 == moves.size());

            // Queen is forked by kngiht, no moves
            board.setPiece(3, 3, Piece(WHITE, QUEEN));
            board.setPiece(3, 5, Piece(WHITE, KING));
            board.setPiece(5, 4, Piece(BLACK, KNIGHT));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(0 == moves.size());
        }

        TEST_METHOD(getKingMovesTest) {
            Board board;
            std::list<Move> moves;

            // King in centre of board, only piece
            // Full range of motion
            board.setPiece(3, 3, Piece(WHITE, KING));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(8 == moves.size());

            // Some same colour pieces next to king, restricting movement
            board.setPiece(2, 3, Piece(WHITE, PAWN));
            board.setPiece(3, 4, Piece(WHITE, QUEEN));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(6 == moves.size());

            // Some opposite colour pawns next to king
            // one is checking king
            // Valid moves to take either of them
            board.setPiece(2, 4, Piece(BLACK, PAWN));
            board.setPiece(4, 2, Piece(BLACK, PAWN));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(6 == moves.size());

            // One of the opposite pawns is protected
            // Can no longer take it
            board.setPiece(5, 2, Piece(BLACK, ROOK));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(5 == moves.size());

            // Opposite colour bishop protects one of previously available squares
            board.setPiece(4, 0, Piece(BLACK, BISHOP));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(4 == moves.size());

            // Opposite colour queen protects more squares
            board.setPiece(4, 6, Piece(BLACK, QUEEN));
            board.setPiece(5, 2, Piece::NO_PIECE);
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(1 == moves.size());

            // Opposte colour bishop protects the last available square
            board.setPiece(5, 0, Piece(BLACK, BISHOP));
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(0 == moves.size());

            // All available squares are checked, only move is to take a checker
            board.setPiece(2, 2, Piece(BLACK, BISHOP));
            board.setPiece(4, 0, Piece::NO_PIECE);
            board.getMovesForPiece(moves, ChessVector(3, 3));
            Assert::IsTrue(1 == moves.size());
        }

        TEST_METHOD(getAllMovesTest) {
            Board board;
            std::list<Move> moves;

            board.setToStartingBoard();
            board.getAllMoves(moves, WHITE);
            Assert::IsTrue(20 == moves.size());
            board.getAllMoves(moves, BLACK);
            Assert::IsTrue(20 == moves.size());
        }

        TEST_METHOD(enPassantTest) {
            Board board;
            std::list<Move> moves;

            board.setPiece(4, 5, Piece(WHITE, PAWN));
            board.setPiece(6, 4, Piece(BLACK, PAWN));

            Assert::IsFalse(board.getEnPassantFlag());
            board.getMovesForPiece(moves, ChessVector(4, 5));
            Assert::IsTrue(1 == moves.size());
            board.getMovesForPiece(moves, ChessVector(6, 4));
            Assert::IsTrue(2 == moves.size());

            // Check that the double pawn move is available for black
            Move doublePawnMove(ChessVector(6, 4), ChessVector(4, 4), Piece(BLACK, PAWN));
            bool movesContainsDoublePawnMove = false;
            for (Move& move : moves) {
                if (move == doublePawnMove) {
                    movesContainsDoublePawnMove = true;
                }
            }
            Assert::IsTrue(movesContainsDoublePawnMove);

            // Do double pawn move, setting up conditions for en passant
            board.doMove(doublePawnMove);
            Assert::IsTrue(board.getEnPassantFlag());
            board.getMovesForPiece(moves, ChessVector(4, 5));
            Assert::IsTrue(2 == moves.size());

            // Check that the en passant move is available for white
            Move enPassantMove(ChessVector(4, 5), ChessVector(5, 4), Piece(WHITE, PAWN), EN_PASSANT);
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
            board.getMovesForPiece(moves, ChessVector(4, 5));
            Assert::IsTrue(1 == moves.size());

            // Do en passant (despite being illegal because the white pawn is pinned)
            // Check that the black pawn is removed from the board
            board.doMove(enPassantMove);
            Assert::IsTrue(board.getPiece(4, 4) == Piece::NO_PIECE);
        }

        TEST_METHOD(castleTest) {
            Board board;
            std::list<Move> moves;

            board.setToStartingBoard();
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

            board.getMovesForPiece(moves, ChessVector(0, 4));
            Assert::IsTrue(7 == moves.size());


        }
    };
}