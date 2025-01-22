
#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Chess;

namespace PieceTests {

    TEST_CLASS(PieceTests) {
    public:
        TEST_METHOD(toStringTest) {
            Piece piece(WHITE, PAWN);
            Assert::IsTrue(piece.getSymbol() == "wP");
        }
    };
}