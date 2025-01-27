
#include <iostream>
#include <string>
#include <sstream>

#include "ConsoleGraphics.hpp"

static bool emptyBoardCreated = false;

void ConsoleGraphics::drawBoard(const Chess::Board& board) {
    std::stringstream stream;

    const std::string HORIZONTAL_LINE = "  -----------------------------------------";
    stream << "\n" << HORIZONTAL_LINE;

    for (char r = 7; r >= 0; r--) {
        stream << "\n" << (char)('1' + r) << " |";

        for (char f = 0; f < 8; f++) {
            stream << " " << board.getPiece(r, f).getSymbol() << " |";
        }

        stream << "\n" << HORIZONTAL_LINE;
    }

    const std::string FILE_LABELS = "     a    b    c    d    e    f    g    h";
    stream << "\n" << FILE_LABELS << "\n";
    std::cout << stream.str();

}
