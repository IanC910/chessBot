
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
    const std::string FILE_LABELS       = "     a    b    c    d    e    f    g    h";

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

    return Piece::NO_PIECE;
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
    if (piece.getType() == KING) {
        if (piece.getColour() == WHITE) {
            whiteKingPos.rank = rank;
            whiteKingPos.file = file;
        }
        else if(piece.getColour() == BLACK) {
            blackKingPos.rank = rank;
            blackKingPos.file = file;
        }
    }
    
    pieces[rank][file] = piece;
}

void Board::setPiece(Position position, const Piece& piece) {
    setPiece(position.rank, position.file, piece);
}

static int sign(int x) {
    return (x > 0) - (x < 0);
}

bool Board::doesMoveCheckOwnKing(const Move& move) {
    if (move.startPiece.getType() == KING) {
        // TODO
    }
    else {
        // A move can only check it's own king if the piece moved was pinned
        // A piece cannot be pinned by queens, bishops, and rooks, not by knights or pawns
        // A piece can be pinned only on horizontal, vertical, or 45 degree lines
        // A piece can be pinned only if it is the only piece between the king and an attacker on a valid pin line

        // Check if piece is initially on a valid pin line
        Colour colour = (Colour)move.startPiece.getColour();
        Position kingPos = getKingPos(colour);

        // Direction from king to start pos
        int startDirRank = move.startPos.rank - kingPos.rank;
        int startDirFile = move.startPos.file - kingPos.file;

        // Valid pin line if horizontal, vertical, or 45 degrees
        bool isValidPinLine =
            (abs(startDirRank) == abs(startDirFile)) ||
            (startDirRank == 0) ||
            (startDirFile == 0);

        if (!isValidPinLine) {
            // The piece is not pinned, therefore cannot check its own king
            return false;
        }

        // Direction from king to end pos
        int endDirRank = move.endPos.rank - kingPos.rank;
        int endDirFile = move.endPos.file - kingPos.file;

        // Check if piece ends on the same pin line
        // If same pin line, startDirRank / startDirFile == endDirRank / endDirFile, but account for 0s in denominator
        bool endsOnSamePinLine =
            (startDirRank * endDirFile == endDirRank * startDirFile) &&
            (sign(startDirRank) == sign(endDirRank)) &&
            (sign(startDirFile) == sign(endDirFile));

        if (endsOnSamePinLine) {
            // The piece is pinned, but it remains pinned after the move
            return false;
        }

        // Check if there is no other defending piece between its king and an attacker after the move
        int normalDirRank = startDirRank;
        int normalDirFile = startDirFile;

        if (startDirRank != 0) {
            normalDirRank = startDirRank / abs(startDirRank);
        }
        if (startDirFile != 0) {
            normalDirFile = startDirFile / abs(startDirFile);
        }

        int rank = kingPos.rank;
        int file = kingPos.file;

        while (true) {
            rank += normalDirRank;
            file += normalDirFile;

            // Skip over the starting position
            if (rank == move.startPos.rank && file == move.startPos.file) {
                continue;
            }

            if (!Position::isValid(rank, file)) {
                // Off the board: the pin line contains no attackers
                return false;
            }

            Piece piece = getPiece(rank, file);
            if (piece.equals(Piece::NO_PIECE)) {
                continue;
            }

            bool isAttacker =
                (piece.getColour() == getOpposite(colour)) &&
                (piece.getType() == QUEEN || piece.getType() == BISHOP || piece.getType() == ROOK);

            if (isAttacker) {
                return true;
            }

            if (piece.getType() != NO_TYPE) {
                // There is a non-attacking piece in the pin line between the king and any attacker
                return false;
            }
        }
    }

    return false;
}

void Board::doMove(const Move& move) {
    if (move.startPos.isValid() && move.endPos.isValid()) {
        setPiece(move.startPos, Piece::NO_PIECE);
        setPiece(move.endPos, move.endPiece);
    }
}

Position Board::getKingPos(Colour colour) {
    if (colour == WHITE) {
        return whiteKingPos;
    }
    else if (colour == BLACK) {
        return blackKingPos;
    }
    
    return Position();
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