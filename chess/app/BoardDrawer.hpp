
#pragma once

#include <string>

#include "../chess.hpp"

class BoardDrawer {
public:
    const char SQUARE_HEIGHT = 5;
    const char SQUARE_WIDTH = 10;

    const char PIECE_HEIGHT = 3;
    const char PIECE_WIDTH = 6;

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
    const int BOARD_WIDTH = SQUARE_WIDTH * 8 + 3 + 1;
    bool emptyBoardCreated = false;
    void cacheEmptyBoard();
    void drawPiece(std::wstring& boardString, char rank, char file, Chess::Piece piece);
    

    std::wstring emptyBoardString;
};

