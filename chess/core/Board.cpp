
#include <string>
#include <sstream>

#include "Move.hpp"
#include "Position.hpp"
#include "Piece.hpp"

#include "Board.hpp"

Board::Board(bool startingBoard) {
    if (startingBoard) {
        setToStartingBoard();
    }
}

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
    const std::string HORIZONTAL_LINE   = "  -----------------------------------------";
    const std::string FILE_LABELS       = "    a    b    c    d    e    f    g    h";

    std::stringstream stream;

    stream << HORIZONTAL_LINE;

    for (char r = 7; r >= 0; r--) {
        stream << "\n" << (char)('1' + r) << " |";

        for (char f = 0; f < 8; f++) {
            stream << " " << getPiece(r, f).getSymbol() << " |";
        }

        stream << "\n" << HORIZONTAL_LINE;
    }

    stream << "\n" << FILE_LABELS << "\n";

    return stream.str();
}

Piece Board::getPiece(char rank, char file) const {
    if (Position::isValid(rank, file)) {
        return pieces[rank][file];
    }

    return Piece();
}

Piece Board::getPiece(Position position) const {
    return getPiece(position.rank, position.file);
}

void Board::setPiece(char rank, char file, const Piece& piece) {
    // If position is not valid
    if (!Position::isValid(rank, file)) {
        return;
    }

    // If current piece is a king
    if (piece.type == KING) {
        if (piece.colour == WHITE) {
            whiteKingPos.rank = rank;
            whiteKingPos.file = file;
        }
        else {
            blackKingPos.rank = rank;
            blackKingPos.file = file;
        }
    }
    
    pieces[rank][file] = piece;
}

void Board::setPiece(Position position, const Piece& piece) {
    setPiece(position.rank, position.file, piece);
}

void Board::doMove(const Move& move) {
    if (move.startPos.isValid() && move.endPos.isValid()) {
        setPiece(move.startPos, Piece::NO_PIECE);
        setPiece(move.endPos, move.endPiece);
    }
}

void Board::clear() {
    for (int r = 0; r < 8; r++) {
        for (int f = 0; f < 8; f++) {
            setPiece(r, f, Piece::NO_PIECE);
        }
    }
}

void Board::setToStartingBoard() {
    clear();

    // Kings
    setPiece(0, 4, Piece(WHITE, KING));
    setPiece(7, 4, Piece(BLACK, KING));

    // Queens
    setPiece(0, 3, Piece(WHITE, QUEEN));
    setPiece(7, 3, Piece(BLACK, QUEEN));

    // Bishops
    setPiece(0, 2, Piece(WHITE, BISHOP));
    setPiece(0, 5, Piece(WHITE, BISHOP));
    setPiece(7, 2, Piece(BLACK, BISHOP));
    setPiece(7, 5, Piece(BLACK, BISHOP));

    // Knights
    setPiece(0, 1, Piece(WHITE, KNIGHT));
    setPiece(0, 6, Piece(WHITE, KNIGHT));
    setPiece(7, 1, Piece(BLACK, KNIGHT));
    setPiece(7, 6, Piece(BLACK, KNIGHT));

    // Rooks
    setPiece(0, 0, Piece(WHITE, ROOK));
    setPiece(0, 7, Piece(WHITE, ROOK));
    setPiece(7, 0, Piece(BLACK, ROOK));
    setPiece(7, 7, Piece(BLACK, ROOK));

    // Pawns
    for (int f = 0; f < 8; f++) {
        setPiece(1, f, Piece(WHITE, PAWN));
        setPiece(6, f, Piece(BLACK, PAWN));
    }
}