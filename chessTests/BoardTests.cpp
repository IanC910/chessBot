
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

			std::cout << board.toString() << std::endl;
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

		TEST_METHOD(checkOwnKingTest) {
            // Diagonal pin line
            // Defender moves out of way and checks own king
            Board board;
            board.setPiece(0, 0, Piece(WHITE, KING));
            board.setPiece(5, 5, Piece(BLACK, BISHOP));
            Move move(Position(1, 1), Position(2, 1), Piece(WHITE, PAWN), Piece(WHITE, PAWN));
            Assert::IsTrue(board.doesMoveCheckOwnKing(move));

            // Horizontal pin line
            // Defender moves out of way and checks own king
            board.clear();
            board.setPiece(7, 7, Piece(BLACK, KING));
            board.setPiece(7, 0, Piece(WHITE, ROOK));
            move = Move(Position(7, 6), Position(6, 6), Piece(BLACK, ROOK), Piece(BLACK, ROOK));
            Assert::IsTrue(board.doesMoveCheckOwnKing(move));

            // Horizontal pin line
            // Defender moves within the pin line, does not check own king
            board.clear();
            board.setPiece(7, 7, Piece(BLACK, KING));
            board.setPiece(7, 0, Piece(WHITE, ROOK));
            move = Move(Position(7, 6), Position(7, 5), Piece(BLACK, ROOK), Piece(BLACK, ROOK));
            Assert::IsFalse(board.doesMoveCheckOwnKing(move));

            // Vertical pin line
            // Multiple defenders, all of kings colour
            // One defender moves out of pin line, does not check own king
            board.clear();
            board.setPiece(0, 5, Piece(WHITE, KING));
            board.setPiece(1, 5, Piece(WHITE, KNIGHT));
            board.setPiece(7, 5, Piece(BLACK, QUEEN));
            move = Move(Position(5, 5), Position(1, 1), Piece(WHITE, QUEEN), Piece(WHITE, QUEEN));
            Assert::IsFalse(board.doesMoveCheckOwnKing(move));

            // Vertical pin line
            // Multiple defenders, not all of kings colour
            // One defender moves out of pin line, does not check own king
            board.clear();
            board.setPiece(0, 5, Piece(WHITE, KING));
            board.setPiece(1, 5, Piece(BLACK, KNIGHT));
            board.setPiece(7, 5, Piece(BLACK, QUEEN));
            move = Move(Position(5, 5), Position(1, 1), Piece(WHITE, QUEEN), Piece(WHITE, QUEEN));
            Assert::IsFalse(board.doesMoveCheckOwnKing(move));
            std::cout << board.toString();

            // Diagonal pin line
            // No Attacker, so move does not check own king
            board.clear();
            board.setPiece(4, 5, Piece(WHITE, KING));
            move = Move(Position(6, 3), Position(4, 4), Piece(WHITE, KNIGHT), Piece(WHITE, KNIGHT));
            Assert::IsFalse(board.doesMoveCheckOwnKing(move));
		}
	};
}
