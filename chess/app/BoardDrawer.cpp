
#include <iostream>
#include <string>
#include <sstream>

#include "BoardDrawer.hpp"

static char NO_PIECE_BITMAP[] = {
    0,0,0,0,0,0,
    0,0,0,0,0,0,
    0,0,0,0,0,0
};

static char PAWN_BITMAP[] = {
    0,0,0,0,0,0,
    0,0,1,1,0,0,
    0,1,1,1,1,0
};

static char BISHOP_BITMAP[] = {
    0,0,1,1,0,0,
    0,1,1,1,1,0,
    0,1,1,1,1,0
};

static char KNIGHT_BITMAP[] = {
    0,1,1,1,0,0,
    0,0,1,1,1,0,
    1,1,1,1,1,1
};

static char ROOK_BITMAP[] = {
    1,0,1,1,0,1,
    0,1,1,1,1,0,
    1,1,1,1,1,1
};

static char QUEEN_BITMAP[] = {
    0,1,0,0,1,0,
    1,0,1,1,0,1,
    0,1,1,1,1,0
};

static char KING_BITMAP[] = {
    1,0,1,1,0,1,
    1,1,1,1,1,1,
    0,1,1,1,1,0
};

static char* BITMAPS[] = {
    nullptr,
    PAWN_BITMAP,
    BISHOP_BITMAP,
    KNIGHT_BITMAP,
    ROOK_BITMAP,
    QUEEN_BITMAP,
    KING_BITMAP
};

void BoardDrawer::drawBoard(const Chess::Board& board) {
    std::stringstream stream;

    cacheEmptyBoard();

    std::wstring boardString = emptyBoardString;

    for (char r = 0; r < 8; r++) {
        for (char f = 0; f < 8; f++) {
            Chess::Piece piece = board.getPiece(r, f);
            if (piece.getColour() != Chess::NO_COLOUR) {
                drawPiece(boardString, r, f, piece);
            }
        }
    }
    

    std::wcout << "\n" << boardString << "\n";
}

void BoardDrawer::cacheEmptyBoard() {
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

    emptyBoardString = emptyBoardStream.str();
}

void BoardDrawer::drawPiece(std::wstring& boardString, char rank, char file, Chess::Piece piece) {
    if (!Chess::Vector::isValid(rank, file)) {
        return;
    }

    wchar_t colourChars[] = {GREY, WHITE_PIECE_CHAR, BLACK_PIECE_CHAR};
    wchar_t pieceChar = colourChars[piece.getColour()];
    char* bitmap = BITMAPS[piece.getType()];

    int startRow = 1 + (7 - rank) * SQUARE_HEIGHT;
    int startCol = 3 + 2 + file * SQUARE_WIDTH;

    for (int i = 0; i < PIECE_HEIGHT; i++) {
        for (int j = 0; j < PIECE_WIDTH; j++) {
            if(bitmap[i * PIECE_WIDTH + j]) {
                boardString[(i + startRow) * BOARD_WIDTH + j + startCol] = pieceChar;
            }
        }
    }
}
