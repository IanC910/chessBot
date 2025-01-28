
#pragma once

#include <string>

#include "../chess.hpp"

class ConsoleGraphics {
public:
    const char SQUARE_HEIGHT = 5;
    const char SQUARE_WIDTH = 9;

    const wchar_t WHITE         = 219;
    const wchar_t LIGHT_GREY    = 178;
    const wchar_t GREY          = 176;
    const wchar_t BLACK         = ' ';

    const wchar_t WHITE_SQUARE_CHAR = LIGHT_GREY;
    const wchar_t BLACK_SQUARE_CHAR = GREY;

    const wchar_t WHITE_PIECE_CHAR = WHITE;
    const wchar_t BLACK_PIECE_CHAR = BLACK;


    void drawBoard(const Chess::Board& board);

private:
    void cacheEmptyBoard();

    bool emptyBoardCreated = false;
    std::wstring emptyBoard;
};

