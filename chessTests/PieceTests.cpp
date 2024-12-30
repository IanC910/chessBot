
#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PieceTests {

    TEST_CLASS(PieceTests) {
    public:
        TEST_METHOD(toStringTest) {
            Piece piece(WHITE, PAWN);

            std::cout << "String: " << piece.getSymbol() << "\n";

            Assert::IsTrue(piece.getSymbol() == "wP");
        }
    };
}