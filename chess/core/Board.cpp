
#include <cstring>
#include <list>
#include <sstream>
#include <string>

#include "Move.hpp"
#include "Vector.hpp"
#include "Piece.hpp"

#include "Board.hpp"

using namespace Chess;

Board::Board() {}

Board::Board(const Board& board) {
    memcpy(this->pieces, board.pieces, 64 * sizeof(Piece));

    lastMoveWasDoublePawn       = board.lastMoveWasDoublePawn;
    positionOfLastMove  = board.positionOfLastMove;

    whiteCanShortCastle = board.whiteCanShortCastle;
    whiteCanLongCastle  = board.whiteCanLongCastle;
    blackCanShortCastle = board.blackCanShortCastle;
    blackCanLongCastle  = board.blackCanLongCastle;
}

bool Board::equals(const Board& board) const {
    for (int r = 0; r < 8; r++) {
        for (int f = 0; f < 8; f++) {
            if (this->getPiece(r, f) != board.getPiece(r, f)) {
                return false;
            }
        }
    }

    return true;
}

bool Board::operator==(const Board& board) const {
    return equals(board);
}

bool Board::operator!=(const Board& board) const {
    return !equals(board);
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
    if (Vector::isValid(rank, file)) {
        return pieces[rank][file];
    }

    return Piece::NO_PIECE;
}

Piece Board::getPiece(Vector position) const {
    return getPiece(position.rank, position.file);
}

void Board::setPiece(char rank, char file, const Piece& piece) {
    // If position is not valid
    if (!Vector::isValid(rank, file)) {
        return;
    }
    
    pieces[rank][file] = piece;
}

void Board::setPiece(Vector position, const Piece& piece) {
    setPiece(position.rank, position.file, piece);
}

void Board::clear() {
    for (int r = 0; r < 8; r++) {
        for (int f = 0; f < 8; f++) {
            setPiece(r, f, Piece::NO_PIECE);
        }
    }
}

void Board::reset() {
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

    positionOfLastMove = Vector::INVALID;
    lastMoveWasDoublePawn       = false;

    whiteCanShortCastle = true;
    whiteCanLongCastle  = true;

    blackCanShortCastle = true;
    blackCanLongCastle  = true;
}

Vector Board::getPositionOfLastMove() const {
    return positionOfLastMove;
}

bool Board::wasLastMoveDoublePawn() const {
    return lastMoveWasDoublePawn;
}

bool Board::canColourShortCastle(Colour colour) const {
    switch (colour) {
        case WHITE:
            return whiteCanShortCastle;
        case BLACK:
            return blackCanShortCastle;
        default:
            return false;
    }
}

bool Board::canColourLongCastle(Colour colour) const {
    switch (colour) {
    case WHITE:
        return whiteCanLongCastle;
    case BLACK:
        return blackCanLongCastle;
    default:
        return false;
    }
}

void Board::doMove(const Move& move) {
    if (move.startPos.isValid() && move.endPos.isValid()) {
        setPiece(move.startPos, Piece::NO_PIECE);
        setPiece(move.endPos, move.endPiece);

        positionOfLastMove = move.endPos;
        lastMoveWasDoublePawn = false;

        switch (move.endPiece.getType()) {
            case PAWN: {
                bool startedOnStartRank = (move.startPos.rank == move.endPiece.getStartRank());
                bool endedOnDoubleMoveEndRank = (move.endPos.rank ==
                    move.endPiece.getStartRank() + 2 * move.endPiece.getForwardDirection()
                );
                lastMoveWasDoublePawn = (startedOnStartRank && endedOnDoubleMoveEndRank);
                break;
            }
            case ROOK: {
                if (move.endPiece.getColour() == WHITE) {
                    if (move.startPos == Vector(0, 7)) {
                        whiteCanShortCastle = false;
                    }
                    else if (move.startPos == Vector(0, 0)) {
                        whiteCanLongCastle = false;
                    }
                }
                else if (move.endPiece.getColour() == BLACK) {
                    if (move.startPos == Vector(7, 7)) {
                        blackCanShortCastle = false;
                    }
                    else if (move.startPos == Vector(7, 0)) {
                        blackCanLongCastle = false;
                    }
                }
                break;
            }
            case KING: {
                if (move.endPiece.getColour() == WHITE) {
                    whiteCanShortCastle = false;
                    whiteCanLongCastle = false;
                }
                else {
                    blackCanShortCastle = false;
                    blackCanLongCastle = false;
                }
                break;
            }
            default:
                break;
        }

        switch (move.specialType) {
            case EN_PASSANT: {
                setPiece(
                    move.endPos.rank - move.endPiece.getForwardDirection(),
                    move.endPos.file,
                    Piece::NO_PIECE
                );
                break;
            }
            case SHORT_CASTLE: {
                setPiece(move.endPiece.getStartRank(), 7, Piece::NO_PIECE);
                setPiece(move.endPiece.getStartRank(), 5, Piece(move.endPiece.getColour(), ROOK));
                break;
            }
            case LONG_CASTLE: {
                setPiece(move.endPiece.getStartRank(), 0, Piece::NO_PIECE);
                setPiece(move.endPiece.getStartRank(), 3, Piece(move.endPiece.getColour(), ROOK));
                break;
            }
            default:
                break;
        }
    }
}

int Board::getMaterialValue() const {
    int materialValue = 0;

    for (int r = 0; r < 8; r++) {
        for (int f = 0; f < 8; f++) {
            materialValue += getPiece(r, f).getValue();
        }
    }

    return materialValue;
}

bool Board::hasInsufficientMaterial() {
    std::list<Vector> positionsForColour[3];

    for (int r = 0; r < 8; r++) {
        for (int f = 0; f < 8; f++) {
            Piece piece = getPiece(r, f);
            if(piece.getColour() != NO_COLOUR) {
                positionsForColour[piece.getColour()].emplace_back(r, f);
            }
        }

        if (positionsForColour[WHITE].size() > 2 || positionsForColour[BLACK].size() > 2) {
            return false;
        }
    }

    bool whiteHasInsufficientMaterial = true;
    std::list<Vector>::iterator posIt = positionsForColour[WHITE].begin();
    while (posIt != positionsForColour[WHITE].end()) {
        Piece piece = getPiece(*posIt);
        if (piece.getType() != BISHOP && piece.getType() != KNIGHT && piece.getType() != KING) {
            whiteHasInsufficientMaterial = false;
            break;
        }
        ++posIt;
    }

    bool blackHasInsufficientMaterial = true;
    posIt = positionsForColour[BLACK].begin();
    while (posIt != positionsForColour[BLACK].end()) {
        Piece piece = getPiece(*posIt);
        if (piece.getType() != BISHOP && piece.getType() != KNIGHT && piece.getType() != KING) {
            blackHasInsufficientMaterial = false;
            break;
        }
        ++posIt;
    }

    return whiteHasInsufficientMaterial && blackHasInsufficientMaterial;
}

uint64_t Board::getPositionCode() {
    uint64_t positionCode = 0;

    for (int r = 0; r < 8; r++) {
        for (int f = 0; f < 8; f++) {
            Piece piece = getPiece(r, f);
            uint64_t bit = piece.getColour() != NO_COLOUR;
            positionCode |= bit << (r * 8 + f);
        }
    }

    return positionCode;
}

