
#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BoardTests {

	TEST_CLASS(BoardTests) {
	public:
		TEST_METHOD(constructorTest) {
			Board board;

			for (int r = 0; r < 8; r++) {
				for (int f = 0; f < 8; f++) {
					Assert::IsTrue(board.getPiece(r, f).equals(Piece::NO_PIECE));
				}
			}
		}

		TEST_METHOD(toStringTest) {
			Board board(true);
			std::cout << board.toString();
		}

		TEST_METHOD(copyTest) {
			Board board(true);
			Board copy(board);
			Assert::IsTrue(board.equals(copy));

			copy.setPiece(4, 4, Piece(WHITE, PAWN));
			Assert::IsFalse(board.equals(copy));

			board.setPiece(4, 4, Piece(WHITE, PAWN));
			Assert::IsTrue(board.equals(copy));
		}

        TEST_METHOD(isPiecePinnedTest) {
            // Diagonal pin line
            Board board;
            board.setPiece(0, 0, Piece(WHITE, KING));
            board.setPiece(5, 5, Piece(BLACK, BISHOP));
            board.setPiece(1, 1, Piece(WHITE, PAWN));
            Assert::IsTrue(board.isPiecePinned(ChessVector(1, 1)));

            // Horizontal pin line
            board.clear();
            board.setPiece(7, 7, Piece(BLACK, KING));
            board.setPiece(7, 0, Piece(WHITE, ROOK));
            board.setPiece(7, 6, Piece(BLACK, ROOK));
            Assert::IsTrue(board.isPiecePinned(ChessVector(7, 6)));

            // Vertical pin line
            // Multiple defenders, all of kings colour
            // One defender moves out of pin line, does not check own king
            board.clear();
            board.setPiece(0, 5, Piece(WHITE, KING));
            board.setPiece(1, 5, Piece(WHITE, KNIGHT));
            board.setPiece(7, 5, Piece(BLACK, QUEEN));
            board.setPiece(5, 5, Piece(WHITE, QUEEN));
            Assert::IsFalse(board.isPiecePinned(ChessVector(5, 5)));

            // Vertical pin line
            // Multiple defenders, not all of kings colour
            // One defender moves out of pin line, does not check own king
            board.clear();
            board.setPiece(0, 5, Piece(WHITE, KING));
            board.setPiece(1, 5, Piece(BLACK, KNIGHT));
            board.setPiece(7, 5, Piece(BLACK, QUEEN));
            board.setPiece(5, 5, Piece(WHITE, QUEEN));
            Assert::IsFalse(board.isPiecePinned(ChessVector(5, 5)));

            // Diagonal pin line
            // No Attacker, so move does not check own king
            board.clear();
            board.setPiece(4, 5, Piece(WHITE, KING));
            board.setPiece(6, 3, Piece(WHITE, KNIGHT));
            Assert::IsFalse(board.isPiecePinned(ChessVector(6, 3)));
        }

		TEST_METHOD(checkOwnKingTest) {
            // Defender moves out of way and checks own king
            Board board;
            board.setPiece(0, 0, Piece(WHITE, KING));
            board.setPiece(5, 5, Piece(BLACK, BISHOP));
            Move move(ChessVector(1, 1), ChessVector(2, 1), Piece(WHITE, PAWN), Piece(WHITE, PAWN));
            Assert::IsTrue(board.doesMoveCheckOwnKing(move));

            // Horizontal pin line
            // Defender moves out of way and checks own king
            board.clear();
            board.setPiece(7, 7, Piece(BLACK, KING));
            board.setPiece(7, 0, Piece(WHITE, ROOK));
            move = Move(ChessVector(7, 6), ChessVector(6, 6), Piece(BLACK, ROOK), Piece(BLACK, ROOK));
            Assert::IsTrue(board.doesMoveCheckOwnKing(move));

            // Horizontal pin line
            // Defender moves within the pin line, does not check own king
            board.clear();
            board.setPiece(7, 7, Piece(BLACK, KING));
            board.setPiece(7, 0, Piece(WHITE, ROOK));
            move = Move(ChessVector(7, 6), ChessVector(7, 5), Piece(BLACK, ROOK), Piece(BLACK, ROOK));
            Assert::IsFalse(board.doesMoveCheckOwnKing(move));

            // Vertical pin line
            // Multiple defenders, all of kings colour
            // One defender moves out of pin line, does not check own king
            board.clear();
            board.setPiece(0, 5, Piece(WHITE, KING));
            board.setPiece(1, 5, Piece(WHITE, KNIGHT));
            board.setPiece(7, 5, Piece(BLACK, QUEEN));
            move = Move(ChessVector(5, 5), ChessVector(1, 1), Piece(WHITE, QUEEN), Piece(WHITE, QUEEN));
            Assert::IsFalse(board.doesMoveCheckOwnKing(move));

            // Vertical pin line
            // Multiple defenders, not all of kings colour
            // One defender moves out of pin line, does not check own king
            board.clear();
            board.setPiece(0, 5, Piece(WHITE, KING));
            board.setPiece(1, 5, Piece(BLACK, KNIGHT));
            board.setPiece(7, 5, Piece(BLACK, QUEEN));
            move = Move(ChessVector(5, 5), ChessVector(1, 1), Piece(WHITE, QUEEN), Piece(WHITE, QUEEN));
            Assert::IsFalse(board.doesMoveCheckOwnKing(move));

            // Diagonal pin line
            // No Attacker, so move does not check own king
            board.clear();
            board.setPiece(4, 5, Piece(WHITE, KING));
            move = Move(ChessVector(6, 3), ChessVector(4, 4), Piece(WHITE, KNIGHT), Piece(WHITE, KNIGHT));
            Assert::IsFalse(board.doesMoveCheckOwnKing(move));
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
