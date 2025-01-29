
#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Chess;

namespace BoardBasicTests {

	TEST_CLASS(BoardBasicTests) {
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
			Board board;
            board.reset();
			std::cout << board.toString();
		}

		TEST_METHOD(copyTest) {
			Board board;
            board.reset();
			Board copy(board);
			Assert::IsTrue(board.equals(copy));

			copy.setPiece(4, 4, Piece(WHITE, PAWN));
			Assert::IsFalse(board.equals(copy));

			board.setPiece(4, 4, Piece(WHITE, PAWN));
			Assert::IsTrue(board.equals(copy));
		}

        TEST_METHOD(pinDirectionTest) {
            // Diagonal pin line
            Board board;
            board.setPiece(0, 0, Piece(WHITE, KING));
            board.setPiece(5, 5, Piece(BLACK, BISHOP));
            board.setPiece(1, 1, Piece(WHITE, PAWN));
            Assert::IsTrue(
                board.getPinDirection(Vector(1, 1))
                .equals(Vector(1, 1))
            );

            // Horizontal pin line
            board.clear();
            board.setPiece(7, 7, Piece(BLACK, KING));
            board.setPiece(7, 0, Piece(WHITE, ROOK));
            board.setPiece(7, 6, Piece(BLACK, ROOK));
            Assert::IsTrue(
                board.getPinDirection(Vector(7, 6))
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
            Assert::IsTrue(
                board.getPinDirection(Vector(5, 5))
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
            Assert::IsTrue(
                board.getPinDirection(Vector(5, 5))
                .equals(Vector(0, 0))
            );

            // Diagonal pin line
            // No Attacker, so move does not check own king
            board.clear();
            board.setPiece(4, 5, Piece(WHITE, KING));
            board.setPiece(6, 3, Piece(WHITE, KNIGHT));
            Assert::IsTrue(
                board.getPinDirection(Vector(6, 3))
                .equals(Vector(0, 0))
            );

            // King, same colour pawn, and opposite rook are on the same diagonal
            // Rook doesn't attack diagonally, pawn is not pinned
            board.clear();
            board.setPiece(0, 0, Piece(WHITE, KING));
            board.setPiece(1, 1, Piece(WHITE, PAWN));
            board.setPiece(2, 2, Piece(BLACK, ROOK));
            Assert::IsTrue(
                board.getPinDirection(Vector(1, 1))
                .equals(Vector(0, 0))
            );
        }
    };
}