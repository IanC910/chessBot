
#include <string>
#include <sstream>
#include <cstring>

#include "Move.hpp"
#include "ChessVector.hpp"
#include "Piece.hpp"

#include "Board.hpp"

Board::Board(bool startingBoard) {
    if (startingBoard) {
        setToStartingBoard();
    }
}

Board::Board(const Board& board) {
    memcpy(this->pieces, board.pieces, 64 * sizeof(Piece));

    whiteKingPos = board.whiteKingPos;
    blackKingPos = board.blackKingPos;
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
    if (ChessVector::isValid(rank, file)) {
        return pieces[rank][file];
    }

    return Piece::NO_PIECE;
}

Piece Board::getPiece(ChessVector position) const {
    return getPiece(position.rank, position.file);
}

void Board::setPiece(char rank, char file, const Piece& piece) {
    // If position is not valid
    if (!ChessVector::isValid(rank, file)) {
        return;
    }

    // If previous piece is a king
    if (pieces[rank][file].getType() == KING) {
        if (pieces[rank][file].getColour() == WHITE) {
            whiteKingPos = ChessVector::INVALID_VEC;
        }
        else if (pieces[rank][file].getColour() == BLACK) {
            blackKingPos = ChessVector::INVALID_VEC;
        }
    }

    // If new piece is a king
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

void Board::setPiece(ChessVector position, const Piece& piece) {
    setPiece(position.rank, position.file, piece);
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

ChessVector Board::getKingPos(Colour colour) {
    switch (colour) {
        case WHITE:
            return whiteKingPos;
        case BLACK:
            return blackKingPos;
        default:
            return ChessVector::INVALID_VEC;
    }
}

static int sign(int x) {
    return (x > 0) - (x < 0);
}

bool Board::isPiecePinned(ChessVector position) {
    Piece piece = getPiece(position);
    if (!position.isValid()) {
        return false;
    }

    Colour colour = piece.getColour();
    if (colour == NO_COLOUR) {
        return false;
    }
    
    // A piece can be pinned by queens, bishops, and rooks, not by knights or pawns
    // A piece can be pinned only on horizontal, vertical, or 45 degree lines
    // A piece can be pinned only if it is the only piece between the king and an attacker on a valid pin line

    // Check if piece is on a possible pin line
    ChessVector kingPos = getKingPos(colour);
    if (!kingPos.isValid()) {
        return false;
    }

    // Direction from king to piece
    ChessVector difference = position.subtract(kingPos);

    // Valid pin line if horizontal, vertical, or 45 degrees
    bool isValidPinLine =
        (abs(difference.rank) == abs(difference.file)) ||
        (difference.rank == 0) ||
        (difference.file == 0);

    if (!isValidPinLine) {
        return false;
    }

    // Check if there is an attacker on this line and
    // if piece is the only piece between its king and the attacker
    ChessVector directionNormed = difference;

    if (difference.rank != 0) {
        directionNormed.rank = difference.rank / abs(difference.rank);
    }
    if (difference.file != 0) {
        directionNormed.file = difference.file / abs(difference.file);
    }

    ChessVector currPos = kingPos;

    while (true) {
        currPos.increaseBy(directionNormed);

        // Skip over the starting position
        if (currPos.equals(position)) {
            continue;
        }

        if (!currPos.isValid()) {
            // Off the board: the pin line contains no attackers
            return false;
        }

        Piece currPiece = getPiece(currPos);
        if (currPiece.equals(Piece::NO_PIECE)) {
            continue;
        }

        bool isAttacker =
            (currPiece.getColour() == getOppositeColour(piece.getColour())) &&
            (currPiece.getType() == QUEEN || currPiece.getType() == BISHOP || currPiece.getType() == ROOK);

        if (isAttacker) {
            return true;
        }

        if (currPiece.getType() != NO_TYPE) {
            // There is another non-attacking piece in the pin line between the king and any attacker
            return false;
        }
    }
}

int Board::getNumChecks(Colour kingColour) {
    if (kingColour == NO_COLOUR) {
        return 0;
    }

    Colour oppositeColour = getOppositeColour(kingColour);
    ChessVector kingPos = getKingPos(kingColour);
    if (!kingPos.isValid()) {
        return 0;
    }

    Piece king = getPiece(kingPos);
    int numChecks = 0;
    std::list<ChessVector> targetedSquares;

    // Pawn checks
    addTargetedSquaresByPawn(targetedSquares, kingPos);
    for (ChessVector square : targetedSquares) {
        Piece piece = getPiece(square);
        if (piece.getColour() == oppositeColour) {
            if (piece.getType() == PAWN) {
                numChecks++;
            }
        }
    }

    // Diagonal checks
    targetedSquares.clear();
    addTargetedSquaresByBishop(targetedSquares, kingPos);
    for (ChessVector square : targetedSquares) {
        Piece piece = getPiece(square);
        if (piece.getColour() == oppositeColour) {
            if (piece.getType() == BISHOP || piece.getType() == QUEEN) {
                numChecks++;
            }
        }
    }

    // Vertical and horizontal checks
    targetedSquares.clear();
    addTargetedSquaresByRook(targetedSquares, kingPos);
    for (ChessVector square : targetedSquares) {
        Piece piece = getPiece(square);
        if (piece.getColour() == oppositeColour) {
            if (piece.getType() == ROOK || piece.getType() == QUEEN) {
                numChecks++;
            }
        }
    }

    // Knight checks
    targetedSquares.clear();
    addTargetedSquaresByKnight(targetedSquares, kingPos);
    for (ChessVector square : targetedSquares) {
        Piece piece = getPiece(square);
        if (piece.getColour() == oppositeColour) {
            if (piece.getType() == KNIGHT) {
                numChecks++;
            }
        }
    }

    return numChecks;
}

bool Board::isKingChecked(Colour kingColour) {
    return getNumChecks(kingColour) > 0;
}

// Old: Refactor or deprecate
bool Board::doesMoveCheckOwnKing(const Move& move) {
    if (move.startPiece.getType() == KING) {
        // TODO
    }
    else {
        // A move can only check it's own king if the piece moved was pinned
        // A piece can be pinned by queens, bishops, and rooks, not by knights or pawns
        // A piece can be pinned only on horizontal, vertical, or 45 degree lines
        // A piece can be pinned only if it is the only piece between the king and an attacker on a valid pin line

        // Check if piece is initially on a valid pin line
        Colour colour = (Colour)move.startPiece.getColour();
        ChessVector kingPos = getKingPos(colour);
        if (!kingPos.isValid()) {
            return false;
        }

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
            // The piece may be pinned, but it remains pinned after the move
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

            if (!ChessVector::isValid(rank, file)) {
                // Off the board: the pin line contains no attackers
                return false;
            }

            Piece piece = getPiece(rank, file);
            if (piece.equals(Piece::NO_PIECE)) {
                continue;
            }

            bool isAttacker =
                (piece.getColour() == getOppositeColour(colour)) &&
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

void Board::getTargetedSquares(std::list<ChessVector>& targetedSquares, ChessVector position) {
    targetedSquares.clear();

    switch (getPiece(position).getType()) {
        case PAWN:
            addTargetedSquaresByPawn(targetedSquares, position);
            break;
        case BISHOP:
            addTargetedSquaresByBishop(targetedSquares, position);
            break;
        case KNIGHT:
            addTargetedSquaresByKnight(targetedSquares, position);
            break;
        case ROOK:
            addTargetedSquaresByRook(targetedSquares, position);
            break;
        case QUEEN:
            addTargetedSquaresByQueen(targetedSquares, position);
            break;
        case KING:
            addTargetedSquaresByKing(targetedSquares, position);
            break;
        default:
            break;
    }
}

void Board::getMoves(std::list<Move>& moves, ChessVector position, bool useSelfCheckFilter) {
    moves.clear();

    switch (getPiece(position).getType()) {
        case PAWN:
            getPawnMoves(moves, position, useSelfCheckFilter);
            break;
        default:
            break;
    }
}

void Board::doMove(const Move& move) {
    if (move.startPos.isValid() && move.endPos.isValid()) {
        setPiece(move.startPos, Piece::NO_PIECE);
        setPiece(move.endPos, move.endPiece);
    }
}

void Board::addTargetedSquaresByPawn(std::list<ChessVector>& targetedSquares, ChessVector position) {
    if (!position.isValid()) {
        return;
    }

    Piece piece = getPiece(position);
    if (piece.getColour() == NO_COLOUR) {
        return;
    }

    ChessVector forwardLeft(
        position.rank + piece.getForwardDirection(),
        position.file - 1
    );

    if (forwardLeft.isValid()) {
        targetedSquares.push_back(forwardLeft);
    }

    ChessVector forwardRight(
        position.rank + piece.getForwardDirection(),
        position.file + 1
    );

    if (forwardRight.isValid()) {
        targetedSquares.push_back(forwardRight);
    }
}

void Board::addTargetedSquaresByBishop(std::list<ChessVector>& targetedSquares, ChessVector position) {
    if (!position.isValid()) {
        return;
    }

    ChessVector directions[4] {
        {1, 1},
        {-1, 1},
        {-1, -1},
        {1, -1}
    };

    for (ChessVector direction : directions) {
        ChessVector currPos = position.add(direction);

        for(int i = 0; i < 7; i++) {
            if (!currPos.isValid()) {
                break;
            }
            
            targetedSquares.push_back(currPos);

            if (!getPiece(currPos).equals(Piece::NO_PIECE)) {
                break;
            }

            currPos.increaseBy(direction);
        }
    }
}

void Board::addTargetedSquaresByKnight(std::list<ChessVector>& targetedSquares, ChessVector position) {
    if (!position.isValid()) {
        return;
    }

    ChessVector directions[8] {
        {2, 1},
        {1, 2},
        {-1, 2},
        {-2, 1},
        {-2, -1},
        {-1, -2},
        {1, -2},
        {2, -1}
    };

    for (ChessVector direction : directions) {
        ChessVector currPos = position.add(direction);
        
        if (currPos.isValid()) {
            targetedSquares.push_back(currPos);
        }
    }
}

void Board::addTargetedSquaresByRook(std::list<ChessVector>& targetedSquares, ChessVector position) {
    if (!position.isValid()) {
        return;
    }

    ChessVector directions[4] {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1}
    };

    for (ChessVector direction : directions) {
        ChessVector currPos = position.add(direction);

        for (int i = 0; i < 7; i++) {
            if (!currPos.isValid()) {
                break;
            }
            
            targetedSquares.push_back(currPos);

            if (!getPiece(currPos).equals(Piece::NO_PIECE)) {
                break;
            }

            currPos.increaseBy(direction);
        }
    }
}

void Board::addTargetedSquaresByQueen(std::list<ChessVector>& targetedSquares, ChessVector position) {
    if (!position.isValid()) {
        return;
    }

    addTargetedSquaresByBishop(targetedSquares, position);
    addTargetedSquaresByRook(targetedSquares, position);
}

void Board::addTargetedSquaresByKing(std::list<ChessVector>& targetedSquares, ChessVector position) {
    if (!position.isValid()) {
        return;
    }

    ChessVector directions[8] {
        {1, 0},
        {1, 1},
        {0, 1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
        {0, -1},
        {1, -1}
    };

    for (ChessVector direction : directions) {
        ChessVector currPos = position.add(direction);

        if (currPos.isValid()) {
            targetedSquares.push_back(currPos);
        }
    }
}

void Board::getPawnMoves(std::list<Move>& moves, ChessVector position, bool useSelfCheckFilter) {
    Piece piece = getPiece(position);
    if (piece.getColour() == NO_COLOUR) {
        return;
    }

    // Non-attacking move
    ChessVector noAttackEndPos(
        position.rank + piece.getForwardDirection(),
        position.file
    );

    if (!noAttackEndPos.isValid()) {
        // Invalid position means off the board. Every other pawn move has the same end rank, so all are invalid
        return;
    }

    if (getPiece(noAttackEndPos).equals(Piece::NO_PIECE)) {
        Move noAttackMove(position, noAttackEndPos, piece, piece);
        if (!useSelfCheckFilter || !doesMoveCheckOwnKing(noAttackMove)) {
            moves.push_back(noAttackMove);
        }
    }

    // Left attacking move
    ChessVector leftAttackEndPos(
        position.rank + piece.getForwardDirection(),
        position.file - 1
    );

    if (leftAttackEndPos.isValid() &&
        getPiece(leftAttackEndPos).getColour() == getOppositeColour(piece.getColour())
    ) {
        Move leftAttackMove(position, leftAttackEndPos, piece, piece);
        if(!useSelfCheckFilter || !doesMoveCheckOwnKing(leftAttackMove)) {
            moves.push_back(leftAttackMove);
        }
    }

    // Right attacking move
    ChessVector rightAttackEndPos(
        position.rank + piece.getForwardDirection(),
        position.file + 1
    );

    if (rightAttackEndPos.isValid() &&
        getPiece(rightAttackEndPos).getColour() == getOppositeColour(piece.getColour())
    ) {
        Move rightAttackMove(position, rightAttackEndPos, piece, piece);
        if (!useSelfCheckFilter || !doesMoveCheckOwnKing(rightAttackMove)) {
            moves.push_back(rightAttackMove);
        }
    }

    // Check for promotions
    if (noAttackEndPos.rank == 0 || noAttackEndPos.rank == 7) {
        int numLegalMoves = moves.size();

        for (int i = 0; i < numLegalMoves; i++) {
            Move move = moves.front();
            moves.pop_front();

            moves.push_back(Move(move.startPos, move.endPos, piece, Piece(piece.getColour(), BISHOP)));
            moves.push_back(Move(move.startPos, move.endPos, piece, Piece(piece.getColour(), KNIGHT)));
            moves.push_back(Move(move.startPos, move.endPos, piece, Piece(piece.getColour(), ROOK)));
            moves.push_back(Move(move.startPos, move.endPos, piece, Piece(piece.getColour(), QUEEN)));
        }
    }
}