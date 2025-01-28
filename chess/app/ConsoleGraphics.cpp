
#include <iostream>
#include <string>
#include <sstream>

#include "ConsoleGraphics.hpp"

void ConsoleGraphics::cacheEmptyBoard() {
    if (emptyBoardCreated) {
        return;
    }
    emptyBoardCreated = true;

    std::wstringstream emptyBoardStream;

    const wchar_t SQUARE_COLOURS[] {BLACK_SQUARE_CHAR, WHITE_SQUARE_CHAR};

    for (char rank = 7; rank >= 0; rank--) {
        for (char h = 0; h < SQUARE_HEIGHT; h++) {
            // Print rank label
            if (h == SQUARE_HEIGHT / 2) {
                emptyBoardStream << " " << (char)(rank + '1') << " ";
            }
            else {
                emptyBoardStream << "   ";
            }

            // Draw colours
            for (char file = 0; file < 8; file++) {
                for (char w = 0; w < SQUARE_WIDTH; w++) {
                    emptyBoardStream << SQUARE_COLOURS[(rank + file) % 2];
                }
            }

            emptyBoardStream << "\n";
        }
    }

    // Print file labels
    emptyBoardStream << "   ";
    for (char file = 0; file < 8; file++) {
        for (char w = 0; w < SQUARE_WIDTH; w++) {
            if (w == SQUARE_WIDTH / 2) {
                emptyBoardStream << (char)(file + 'a');
            }
            else {
                emptyBoardStream << " ";
            }
        }
    }
    emptyBoardStream << "\n";

    emptyBoard = emptyBoardStream.str();
}

void ConsoleGraphics::drawBoard(const Chess::Board& board) {
    std::stringstream stream;

    cacheEmptyBoard();

    const std::string HORIZONTAL_LINE = "  -----------------------------------------";
    stream << "\n" << HORIZONTAL_LINE;

    for (char r = 7; r >= 0; r--) {
        // Print rank label
        stream << "\n" << (char)('1' + r) << " |";

        for (char f = 0; f < 8; f++) {
            stream << " " << board.getPiece(r, f).getSymbol() << " |";
        }

        stream << "\n" << HORIZONTAL_LINE;
    }

    const std::string FILE_LABELS = "     a    b    c    d    e    f    g    h";
    stream << "\n" << FILE_LABELS << "\n";
    std::cout << stream.str();

    std::wcout << emptyBoard;
}
