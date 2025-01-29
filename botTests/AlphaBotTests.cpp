
#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Chess;

namespace AlphaBotTests {

    TEST_CLASS(AlphaBotTests) {
        TEST_METHOD(priorityTest) {
            Board board;
            AlphaBot alphaBot;

            board.setPiece(0, 5, {WHITE, KING});
            board.setPiece(0, 6, {WHITE, ROOK});
            board.setPiece(1, 7, {WHITE, PAWN});
            board.setPiece(2, 2, {WHITE, PAWN});
            board.setPiece(2, 5, {WHITE, PAWN});
            board.setPiece(1, 6, {WHITE, PAWN});

            board.setPiece(3, 5, {BLACK, PAWN});
            board.setPiece(5, 7, {BLACK, PAWN});
            board.setPiece(7, 1, {BLACK, KNIGHT});
            board.setPiece(7, 5, {BLACK, KING});
            board.setPiece(7, 6, {BLACK, KNIGHT});
            board.setPiece(7, 7, {BLACK, ROOK});

            board.doMove(Move({1, 6}, {3, 6}, {WHITE, PAWN}));

            alphaBot.setColour(BLACK);
            Move botMove = alphaBot.takeTurn(board);

            Assert::IsTrue(EN_PASSANT == botMove.specialType);
        }
    };
}