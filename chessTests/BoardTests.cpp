
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

			board.setPiece(0, 0, Piece(WHITE, ROOK));

			std::cout << board.toString() << std::endl;
		}

		TEST_METHOD(toStringTest) {
			Board* board = Board::createDefaultBoard();

			std::cout << board->toString();
		}
	};
}
