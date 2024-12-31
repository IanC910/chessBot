
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
	};
}
