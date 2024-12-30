
#include <string>
#include <sstream>

#include "Board.hpp"

Board::Board() {}

Board::Board(const Board& board) {
    for (int r = 0; r < 8; r++) {
        for (int f = 0; f < 8; f++) {
            this->setPiece(r, f, board.getPiece(r, f));
        }
    }
}

bool Board::equals(const Board& board) const {
    for (int r = 0; r < 8; r++) {
        for (int f = 0; f < 8; f++) {
            if (!this->getPiece(r, f).equals(board.getPiece(r, f))) {
                return false;
            }
        }
    }

    return true;
}

std::string Board::toString() const {
    const std::string HORIZONTAL_LINE = "-----------------------------------------";

    std::stringstream stream;

    stream << HORIZONTAL_LINE;

    for (int r = 7; r >= 0; r--) {
        stream << "\n|";

        for (int f = 0; f < 8; f++) {
            stream << " " << getPiece(r, f).getSymbol() << " |";
        }

        stream << "\n" << HORIZONTAL_LINE;
    }

    stream << "\n";

    return stream.str();
}

Piece Board::getPiece(char rank, char file) const {
    if (Position::isValid(rank, file)) {
        return tiles[rank][file];
    }

    return Piece();
}

void Board::setPiece(char rank, char file, const Piece& piece) {
    if (Position::isValid(rank, file)) {
        tiles[rank][file] = piece;
    }
}

Board* Board::createDefaultBoard() {
    Board* defaultBoard = new Board();
    
    // Kings
    defaultBoard->setPiece(0, 4, Piece(WHITE, KING));
    defaultBoard->setPiece(7, 4, Piece(BLACK, KING));

    // Queens
    defaultBoard->setPiece(0, 3, Piece(WHITE, QUEEN));
    defaultBoard->setPiece(7, 3, Piece(BLACK, QUEEN));

    // Bishops
    defaultBoard->setPiece(0, 2, Piece(WHITE, BISHOP));
    defaultBoard->setPiece(0, 5, Piece(WHITE, BISHOP));
    defaultBoard->setPiece(7, 2, Piece(BLACK, BISHOP));
    defaultBoard->setPiece(7, 5, Piece(BLACK, BISHOP));

    // Knights
    defaultBoard->setPiece(0, 1, Piece(WHITE, KNIGHT));
    defaultBoard->setPiece(0, 6, Piece(WHITE, KNIGHT));
    defaultBoard->setPiece(7, 1, Piece(BLACK, KNIGHT));
    defaultBoard->setPiece(7, 6, Piece(BLACK, KNIGHT));

    // Rooks
    defaultBoard->setPiece(0, 0, Piece(WHITE, ROOK));
    defaultBoard->setPiece(0, 7, Piece(WHITE, ROOK));
    defaultBoard->setPiece(7, 0, Piece(BLACK, ROOK));
    defaultBoard->setPiece(7, 7, Piece(BLACK, ROOK));

    // Pawns
    for (int f = 0; f < 8; f++) {
        defaultBoard->setPiece(1, f, Piece(WHITE, PAWN));
        defaultBoard->setPiece(6, f, Piece(BLACK, PAWN));
    }

    return defaultBoard;
}