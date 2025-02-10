
#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Chess;

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

        TEST_METHOD(materialValueTest) {
            Board board;
            board.reset();
            Assert::IsTrue(0 == board.getMaterialValue());

            board.setPiece(0, 0, Piece::NO_PIECE);
            Assert::IsTrue(-5 == board.getMaterialValue());
        }

        TEST_METHOD(insufficientMaterialTest) {
            Board board;

            board.setPiece(0, 0, {WHITE, KING});
            board.setPiece(1, 0, {WHITE, PAWN});
            board.setPiece(7, 7, {BLACK, KING});
            Assert::IsFalse(board.hasInsufficientMaterial());

            board.setPiece(1, 0, {WHITE, BISHOP});
            Assert::IsTrue(board.hasInsufficientMaterial());

            board.setPiece(1, 0, Piece::NO_PIECE);
            Assert::IsTrue(board.hasInsufficientMaterial());

            board.setPiece(6, 7, {BLACK, KNIGHT});
            Assert::IsTrue(board.hasInsufficientMaterial());

            board.setPiece(2, 2, {WHITE, KNIGHT});
            Assert::IsTrue(board.hasInsufficientMaterial());

            board.setPiece(1, 2, {WHITE, KNIGHT});
            Assert::IsFalse(board.hasInsufficientMaterial());
        }
    };
}