
#include "pch.h"
#include "CppUnitTest.h"

#include "SequencePlayer.hpp"

#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Chess;

namespace GameTests {

    TEST_CLASS(GameTests) {

        TEST_METHOD(checkMateTest) {
            std::list<Move> moveSequence {
                Move({1, 5}, {2, 5}, {WHITE, PAWN}),
                Move({6, 4}, {4, 4}, {BLACK, PAWN}),
                Move({1, 6}, {3, 6}, {WHITE, PAWN}),
                Move({7, 3}, {3, 7}, {BLACK, QUEEN})
            };

            SequencePlayer player(moveSequence);

            Game game(player, player);

            game.reset();

            Assert::IsTrue(!game.isGameOver());
            Assert::IsTrue(game.getWinnerColour() == NO_COLOUR);

            game.tryNextTurn();
            game.tryNextTurn();
            game.tryNextTurn();
            game.tryNextTurn();

            Assert::IsTrue(game.isGameOver());
            Assert::IsTrue(game.getWinnerColour() == BLACK);
        }
    };

}