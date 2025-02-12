
#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Chess;

namespace TreeWizardBotTests {

    TEST_CLASS(TreeWizardBotTests) {
        TEST_METHOD(blunderTest0) {
            Board board;
            board.setPiece(3, 1, {WHITE, QUEEN});
            board.setPiece(2, 6, {WHITE, KING});
            board.setPiece(1, 4, {BLACK, KING});

            TreeWizardBot treeWizard(3);
            treeWizard.setColour(WHITE);

            Move move = treeWizard.takeTurn(board);

            Logger::WriteMessage(move.toString().c_str());

            Assert::IsFalse(move.startPos == Vector(3, 1) && move.endPos == Vector(1, 3));
        }
    };
}