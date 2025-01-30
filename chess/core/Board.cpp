
#include <string>
#include <sstream>
#include <cstring>

#include "Move.hpp"
#include "Vector.hpp"
#include "Piece.hpp"

#include "Board.hpp"

using namespace Chess;

Board::Board() {}

Board::Board(const Board& board) {
    memcpy(this->pieces, board.pieces, 64 * sizeof(Piece));
    whiteKingPos = board.whiteKingPos;
    blackKingPos = board.blackKingPos;

    enPassantFlag       = board.enPassantFlag;
    positionOfLastMove  = board.positionOfLastMove;

    whiteCanShortCastle = board.whiteCanShortCastle;
    whiteCanLongCastle  = board.whiteCanLongCastle;
    blackCanShortCastle = board.blackCanShortCastle;
    blackCanLongCastle  = board.blackCanLongCastle;

    colourOfCalculatedChecks = board.colourOfCalculatedChecks;
    positionsCheckingKing = board.positionsCheckingKing;
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

    // If previous piece is a king
    if (pieces[rank][file].getType() == KING) {
        if (pieces[rank][file].getColour() == WHITE) {
            whiteKingPos = Vector::INVALID;
        }
        else if (pieces[rank][file].getColour() == BLACK) {
            blackKingPos = Vector::INVALID;
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

    clearCalculatedChecks();
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

    enPassantFlag       = false;

    whiteCanShortCastle = true;
    whiteCanLongCastle  = true;

    blackCanShortCastle = true;
    blackCanLongCastle  = true;

    positionOfLastMove = Vector::INVALID;
    clearCalculatedChecks();
}

Vector Board::getKingPos(Colour colour) const {
    switch (colour) {
        case WHITE:
            return whiteKingPos;
        case BLACK:
            return blackKingPos;
        default:
            return Vector::INVALID;
    }
}

static int sign(int x) {
    return (x > 0) - (x < 0);
}

Vector Board::getPinDirection(Vector position) const {
    Piece piece = getPiece(position);
    if (!position.isValid()) {
        return Vector(0, 0);
    }

    Colour colour = piece.getColour();
    if (colour == NO_COLOUR) {
        return Vector(0, 0);
    }
    
    // A piece can be pinned by queens, bishops, and rooks, not by knights or pawns
    // A piece can be pinned only on horizontal, vertical, or 45 degree lines
    // A piece can be pinned only if it is the only piece between the king and an attacker on a valid pin line

    // Check if piece is on a possible pin line
    Vector kingPos = getKingPos(colour);
    if (!kingPos.isValid()) {
        return Vector(0, 0);
    }

    // Direction from king to piece
    Vector difference = position - kingPos;

    // Valid pin line if horizontal, vertical, or 45 degrees
    bool isDiagonalPinLine = (abs(difference.rank) == abs(difference.file));
    bool isVertOrHorizPinLine = (difference.rank == 0) || (difference.file == 0);

    if (!isDiagonalPinLine && !isVertOrHorizPinLine) {
        // Piece is not a on a valid pin line, can't be pinned
        return Vector(0, 0);
    }

    // Check if there is an attacker on this line and
    // if piece is the only piece between its king and the attacker
    Vector directionNormed = difference;

    if (difference.rank != 0) {
        directionNormed.rank = difference.rank / abs(difference.rank);
    }
    if (difference.file != 0) {
        directionNormed.file = difference.file / abs(difference.file);
    }

    Vector currPos = kingPos;

    while (true) {
        currPos.increaseBy(directionNormed);

        // Skip over the starting position
        if (currPos == position) {
            continue;
        }

        if (!currPos.isValid()) {
            // Off the board: the pin line contains no attackers
            return Vector(0, 0);
        }

        Piece currPiece = getPiece(currPos);
        if (currPiece == Piece::NO_PIECE) {
            continue;
        }

        bool isAttackingColour = (currPiece.getColour() == getOppositeColour(piece.getColour()));
        bool isAttackingType = (
            currPiece.getType() == QUEEN ||
            isDiagonalPinLine && currPiece.getType() == BISHOP ||
            isVertOrHorizPinLine && currPiece.getType() == ROOK
        );

        if (isAttackingColour && isAttackingType) {
            return directionNormed;
        }

        if (currPiece.getType() != NO_PIECE_TYPE) {
            // There is another non-attacking piece in the pin line between the king and any attacker
            return Vector(0, 0);
        }
    }
}

bool Board::isPiecePinned(Vector position) const {
    return getPinDirection(position) != Vector(0, 0);
}

int Board::getNumChecks(Colour kingColour) {
    return getPositionsCheckingKing(kingColour).size();
}

const std::list<Vector>& Board::getPositionsCheckingKing(Colour kingColour) {
    if(kingColour != colourOfCalculatedChecks) {
        calculateChecks(kingColour);
    }
    return positionsCheckingKing;
}

bool Board::isKingChecked(Colour kingColour) {
    return getNumChecks(kingColour) > 0;
}

void Board::clearCalculatedChecks() {
    positionsCheckingKing.clear();
    colourOfCalculatedChecks = NO_COLOUR;
}

bool Board::getEnPassantFlag() const {
    return enPassantFlag;
}

void Board::addSquaresSeenByPiece(std::list<Vector>& squaresSeen, Vector position) const {
    switch (getPiece(position).getType()) {
        case PAWN:
            addSquaresSeenByPawn(squaresSeen, position);
            break;
        case BISHOP:
            addSquaresSeenByBishop(squaresSeen, position);
            break;
        case KNIGHT:
            addSquaresSeenByKnight(squaresSeen, position);
            break;
        case ROOK:
            addSquaresSeenByRook(squaresSeen, position);
            break;
        case QUEEN:
            addSquaresSeenByQueen(squaresSeen, position);
            break;
        case KING:
            addSquaresSeenByKing(squaresSeen, position);
            break;
        default:
            break;
    }
}

void Board::getSquaresSeenByPiece(std::list<Vector>& squaresSeen, Vector position) const {
    squaresSeen.clear();
    addSquaresSeenByPiece(squaresSeen, position);
}

void Board::addMovesForPiece(std::list<Move>& moves, Vector position) {
    Piece piece = getPiece(position);

    switch (piece.getType()) {
        case PAWN: {
            addPawnMoves(moves, position);
            break;
        }
        case BISHOP: {
            addBishopMoves(moves, position);
            break;
        }
        case KNIGHT: {
            addKnightMoves(moves, position);
            break;
        }
        case ROOK: {
            addRookMoves(moves, position);
            break;
        }
        case QUEEN: {
            addQueenMoves(moves, position);
            break;
        }
        case KING:{
            addKingMoves(moves, position);
            break;
        }
        default:
            break;
    }
}

void Board::getMovesForPiece(std::list<Move>& moves, Vector position) {
    moves.clear();
    addMovesForPiece(moves, position);
}

void Board::getAllMoves(std::list<Move>& moves, Colour playerColour) {
    moves.clear();

    for (int r = 0; r < 8; r++) {
        for (int f = 0; f < 8; f++) {
            Piece piece = getPiece(r, f);
            if (piece.getColour() == playerColour) {
                addMovesForPiece(moves, Vector(r, f));
            }
        }
    }
}

void Board::doMove(const Move& move) {
    if (move.startPos.isValid() && move.endPos.isValid()) {
        setPiece(move.startPos, Piece::NO_PIECE);
        setPiece(move.endPos, move.endPiece);

        positionOfLastMove = move.endPos;
        enPassantFlag = false;

        switch (move.endPiece.getType()) {
            case PAWN: {
                // Set en passant flag
                bool correctStartRank = (move.startPos.rank == move.endPiece.getStartRank());
                bool correctEndRank = (move.endPos.rank ==
                    move.endPiece.getStartRank() + 2 * move.endPiece.getForwardDirection()
                );
                enPassantFlag = (correctStartRank && correctEndRank);
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

int Board::getMaterialValue() {
    int materialValue = 0;

    for (int r = 0; r < 8; r++) {
        for (int f = 0; f < 8; f++) {
            materialValue += getPiece(r, f).getValue();
        }
    }

    return materialValue;
}

void Board::calculateChecks(Colour kingColour) {
    colourOfCalculatedChecks = kingColour;
    positionsCheckingKing.clear();

    if (kingColour == NO_COLOUR) {
        return;
    }

    Colour oppositeColour = getOppositeColour(kingColour);
    Vector kingPos = getKingPos(kingColour);
    if (!kingPos.isValid()) {
        return;
    }

    Piece king = getPiece(kingPos);
    std::list<Vector> squaresSeen;

    // Pawn checks
    addSquaresSeenByPawn(squaresSeen, kingPos);
    for (Vector& square : squaresSeen) {
        Piece piece = getPiece(square);
        if (piece.getColour() == oppositeColour) {
            if (piece.getType() == PAWN) {
                positionsCheckingKing.push_back(square);
            }
        }
    }

    // Diagonal checks
    squaresSeen.clear();
    addSquaresSeenByBishop(squaresSeen, kingPos);
    for (Vector& square : squaresSeen) {
        Piece piece = getPiece(square);
        if (piece.getColour() == oppositeColour) {
            if (piece.getType() == BISHOP || piece.getType() == QUEEN) {
                positionsCheckingKing.push_back(square);
            }
        }
    }

    // Vertical and horizontal checks
    squaresSeen.clear();
    addSquaresSeenByRook(squaresSeen, kingPos);
    for (Vector& square : squaresSeen) {
        Piece piece = getPiece(square);
        if (piece.getColour() == oppositeColour) {
            if (piece.getType() == ROOK || piece.getType() == QUEEN) {
                positionsCheckingKing.push_back(square);
            }
        }
    }

    // Knight checks
    squaresSeen.clear();
    addSquaresSeenByKnight(squaresSeen, kingPos);
    for (Vector& square : squaresSeen) {
        Piece piece = getPiece(square);
        if (piece.getColour() == oppositeColour) {
            if (piece.getType() == KNIGHT) {
                positionsCheckingKing.push_back(square);
            }
        }
    }
}

void Board::addSquaresSeenByPawn(std::list<Vector>& squaresSeen, Vector position) const {
    if (!position.isValid()) {
        return;
    }

    Piece piece = getPiece(position);
    if (piece.getColour() == NO_COLOUR) {
        return;
    }

    Vector forwardLeft(
        position.rank + piece.getForwardDirection(),
        position.file - 1
    );

    if (forwardLeft.isValid()) {
        squaresSeen.push_back(forwardLeft);
    }

    Vector forwardRight(
        position.rank + piece.getForwardDirection(),
        position.file + 1
    );

    if (forwardRight.isValid()) {
        squaresSeen.push_back(forwardRight);
    }
}

void Board::addSquaresSeenByBishop(std::list<Vector>& squaresSeen, Vector position) const  {
    if (!position.isValid()) {
        return;
    }

    Vector directions[4] {
        {1, 1},
        {-1, 1},
        {-1, -1},
        {1, -1}
    };

    for (int d = 0; d < 4; ++d) {
        Vector currPos = position + directions[d];

        for(int i = 0; i < 7; i++) {
            if (!currPos.isValid()) {
                break;
            }
            
            squaresSeen.push_back(currPos);

            if (getPiece(currPos) != Piece::NO_PIECE) {
                break;
            }

            currPos.increaseBy(directions[d]);
        }
    }
}

void Board::addSquaresSeenByKnight(std::list<Vector>& squaresSeen, Vector position) const {
    if (!position.isValid()) {
        return;
    }

    Vector directions[8] {
        {2, 1},
        {1, 2},
        {-1, 2},
        {-2, 1},
        {-2, -1},
        {-1, -2},
        {1, -2},
        {2, -1}
    };

    for (int d = 0; d < 8; ++d) {
        Vector currPos = position + directions[d];

        if (currPos.isValid()) {
            squaresSeen.push_back(currPos);
        }
    }
}

void Board::addSquaresSeenByRook(std::list<Vector>& squaresSeen, Vector position) const {
    if (!position.isValid()) {
        return;
    }

    Vector directions[4] {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1}
    };

    for (Vector& direction : directions) {
        Vector currPos = position + direction;

        for (int i = 0; i < 7; i++) {
            if (!currPos.isValid()) {
                break;
            }
            
            squaresSeen.push_back(currPos);

            if (getPiece(currPos) != Piece::NO_PIECE) {
                break;
            }

            currPos.increaseBy(direction);
        }
    }
}

void Board::addSquaresSeenByQueen(std::list<Vector>& squaresSeen, Vector position) const {
    if (!position.isValid()) {
        return;
    }

    addSquaresSeenByBishop(squaresSeen, position);
    addSquaresSeenByRook(squaresSeen, position);
}

void Board::addSquaresSeenByKing(std::list<Vector>& squaresSeen, Vector position) const {
    if (!position.isValid()) {
        return;
    }

    Vector directions[8] {
        {1, 0},
        {1, 1},
        {0, 1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
        {0, -1},
        {1, -1}
    };

    for (int d = 0; d < 8; ++d) {
        Vector currPos = position + directions[d];

        if (currPos.isValid()) {
            squaresSeen.push_back(currPos);
        }
    }
}

void Board::filterEndSquaresByCheckRules(std::list<Vector>& endSquares, Vector startPosition) {
    Piece piece = getPiece(startPosition);
    Colour colour = piece.getColour();

    // Check for pins, filter
    Vector pinDirection = getPinDirection(startPosition);
    if (pinDirection != Vector(0, 0)) {
        std::list<Vector>::iterator endSquareIt = endSquares.begin();
        while (endSquareIt != endSquares.end()) {
            // Invalid move if doesn't end on same pin line
            // I.e. if diff direction != pin direction (different slopes)
            Vector diff = *endSquareIt - startPosition;
            if (diff.file * pinDirection.rank != pinDirection.file * diff.rank) {
                endSquareIt = endSquares.erase(endSquareIt);
            }
            else {
                ++endSquareIt;
            }
        }
    }

    // Check for king checks, filter
    int numChecks = getNumChecks(colour);
    if (numChecks == 1) {
        Vector checkingPosition = getPositionsCheckingKing(colour).front();
        Vector checkDirection = checkingPosition - getKingPos(colour);
        std::list<Vector>::iterator endSquareIt = endSquares.begin();
        while (endSquareIt != endSquares.end()) {
            // Final position must block or take checking piece
            // I.e. Final positon must be on the check line
            // I.e. diff must have the same slope as the check vector and dot product must be positive
            Vector diffFromKing = *endSquareIt - getKingPos(colour);
            Vector diffFromChecker = *endSquareIt - checkingPosition;
            // TODO: Fix same side
            bool sameSlope = (diffFromKing.file * checkDirection.rank == checkDirection.file * diffFromKing.rank);
            bool isBlocking = (diffFromKing.dotProduct(checkDirection) >= 0) && (diffFromChecker.dotProduct(checkDirection.getOpposite()) >= 0);
            if (!sameSlope || !isBlocking) {
                endSquareIt = endSquares.erase(endSquareIt);
            }
            else {
                ++endSquareIt;
            }
        }
    }
}

void Board::filterEndSquaresByAvailability(std::list<Vector>& endSquares, Vector startPosition) const {
    Piece piece = getPiece(startPosition);
    Colour colour = piece.getColour();
    std::list<Vector>::iterator endSquareIt = endSquares.begin();
    while (endSquareIt != endSquares.end()) {
        if (getPiece(*endSquareIt).getColour() == colour) {
            endSquareIt = endSquares.erase(endSquareIt);
        }
        else {
            ++endSquareIt;
        }
    }
}

void Board::addPawnMoves(std::list<Move>& moves, Vector position) {
    Piece pawn = getPiece(position);
    Colour pawnColour = pawn.getColour();
    if (pawnColour == NO_COLOUR) {
        return;
    }

    int numChecks = getNumChecks(pawnColour);
    if (numChecks == 2) {
        return;
    }

    // Non-attacking moves
    Vector noAttackEndPos(position.rank + pawn.getForwardDirection(), position.file);
    if (!noAttackEndPos.isValid()) {
        // Invalid position means off the board. Every other pawn move has the same end rank, so all are invalid
        return;
    }

    std::list<Vector> endSquares;

    // Attacking moves, filter by validity
    addSquaresSeenByPawn(endSquares, position);
    std::list<Vector>::iterator squareIt = endSquares.begin();
    while (squareIt != endSquares.end()) {
        if (getPiece(*squareIt).getColour() != getOppositeColour(pawnColour)) {
            squareIt = endSquares.erase(squareIt);
        }
        else {
            ++squareIt;
        }
    }

    if (getPiece(noAttackEndPos) == Piece::NO_PIECE) {
        endSquares.push_back(noAttackEndPos);

        if (position.rank == pawn.getStartRank()) {
            // Above check implies validity
            Vector doubleNoAttackEndPos = noAttackEndPos;
            doubleNoAttackEndPos.rank += pawn.getForwardDirection();
            if (getPiece(doubleNoAttackEndPos) == Piece::NO_PIECE) {
                endSquares.push_back(doubleNoAttackEndPos);
            }
        }
    }

    // En passant
    // Conditions:
    // Pawn must be on 3rd rank form starting
    // Last move must be a double pawn move that ends right next to this pawn
    // TODO
    Vector enPassantEndPos = Vector::INVALID;
    if (enPassantFlag) {
        bool friendlyOnCorrectRank = (position.rank == pawn.getStartRank() + 3 * pawn.getForwardDirection());
        Vector difference = positionOfLastMove - position;
        bool enemyOnCorrectSquare = (difference.rank == 0 && abs(difference.file) == 1);
        if (friendlyOnCorrectRank && enemyOnCorrectSquare) {
            enPassantEndPos.rank = position.rank + pawn.getForwardDirection();
            enPassantEndPos.file = positionOfLastMove.file;
            endSquares.push_back(enPassantEndPos);
        }
    }

    filterEndSquaresByCheckRules(endSquares, position);

    // Check for promotions
    if (noAttackEndPos.rank == 0 || noAttackEndPos.rank == 7) {
        while(!endSquares.empty()) {
            moves.emplace_back(position, endSquares.front(), Piece(pawnColour, BISHOP));
            moves.emplace_back(position, endSquares.front(), Piece(pawnColour, KNIGHT));
            moves.emplace_back(position, endSquares.front(), Piece(pawnColour, ROOK));
            moves.emplace_back(position, endSquares.front(), Piece(pawnColour, QUEEN));
            endSquares.pop_front();
        }
    }
    else {
        for (Vector& endSquare : endSquares) {
            SpecialMoveType moveType = NO_SPECIAL_MOVE_TYPE;
            if (endSquare == enPassantEndPos) {
                moveType = EN_PASSANT;
            }

            moves.emplace_back(position, endSquare, pawn, moveType);
        }
    }
}

void Board::addBishopMoves(std::list<Move>& moves, Vector position) {
    Piece bishop = getPiece(position);
    Colour bishopColour = bishop.getColour();

    int numChecks = getNumChecks(bishopColour);
    if (numChecks == 2) {
        return;
    }

    std::list<Vector> endSquares;
    addSquaresSeenByBishop(endSquares, position);

    filterEndSquaresByCheckRules(endSquares, position);
    filterEndSquaresByAvailability(endSquares, position);

    for (Vector& endSquare : endSquares) {
        moves.emplace_back(position, endSquare, bishop);
    }
}

void Board::addKnightMoves(std::list<Move>& moves, Vector position) {
    Piece knight = getPiece(position);
    Colour knightColour = knight.getColour();

    int numChecks = getNumChecks(knightColour);
    if (numChecks == 2) {
        return;
    }

    std::list<Vector> endSquares;
    addSquaresSeenByKnight(endSquares, position);

    filterEndSquaresByCheckRules(endSquares, position);
    filterEndSquaresByAvailability(endSquares, position);

    for (Vector& endSquare : endSquares) {
        moves.emplace_back(position, endSquare, knight);
    }
}

void Board::addRookMoves(std::list<Move>& moves, Vector position) {
    Piece rook = getPiece(position);
    Colour rookColour = rook.getColour();

    int numChecks = getNumChecks(rookColour);
    if (numChecks == 2) {
        return;
    }

    std::list<Vector> endSquares;
    addSquaresSeenByRook(endSquares, position);

    filterEndSquaresByCheckRules(endSquares, position);
    filterEndSquaresByAvailability(endSquares, position);

    for (Vector& endSquare : endSquares) {
        moves.emplace_back(position, endSquare, rook);
    }
}

void Board::addQueenMoves(std::list<Move>& moves, Vector position) {
    addBishopMoves(moves, position);
    addRookMoves(moves, position);
}

void Board::addKingMoves(std::list<Move>& moves, Vector position) {
    std::list<Vector> endSquares;
    addSquaresSeenByKing(endSquares, position);
    filterEndSquaresByAvailability(endSquares, position);

    // Find all squares seen by opponent
    // Restrict king from moving to those squares
    // Remove all squares seen by opponent from king's possible end squares

    Piece king = getPiece(position);
    Colour kingColour = king.getColour();
    Colour oppositeColour = getOppositeColour(kingColour);

    // Get all squares seen by enemies
    std::list<Vector> squaresSeenByOpponent;
    for (int r = 0; r < 8; r++) {
        for (int f = 0; f < 8; f++) {
            Piece piece = getPiece(r, f);
            if (piece.getColour() == oppositeColour) {
                addSquaresSeenByPiece(squaresSeenByOpponent, Vector(r, f));
            }
        }
    }

    // Filter out squares seen by enemies
    std::list<Vector>::iterator endSquareIt = endSquares.begin();
    while (endSquareIt != endSquares.end()) {
        bool squareInvalid = false;
        std::list<Vector>::iterator oppSquareIt = squaresSeenByOpponent.begin();
        while (oppSquareIt != squaresSeenByOpponent.end()) {
            if ((*endSquareIt) == (*oppSquareIt)) {
                squareInvalid = true;
                break;
            }
            ++oppSquareIt;
        }

        if (squareInvalid) {
            endSquareIt = endSquares.erase(endSquareIt);
        }
        else {
            ++endSquareIt;
        }
    }

    for (Vector& endSquare : endSquares) {
        moves.emplace_back(position, endSquare, king);
    }

    // Conditions for Castling:
    // King and rook have not moved
    // King is not checked
    // No pieces between king and rook
    // King does not pass through or end on a square seen by an enemy piece
    bool canShortCastle = whiteCanShortCastle;
    bool canLongCastle  = whiteCanLongCastle;
    if (kingColour == BLACK) {
        canShortCastle  = blackCanShortCastle;
        canLongCastle   = blackCanLongCastle;
    }

    if (!isKingChecked(kingColour)) {
        // Short castle
        if (canShortCastle) {
            // Check for no pieces
            char kingRank = king.getStartRank();
            for (char f = 5; f <= 6 && canShortCastle; f++) {
                if (getPiece(kingRank, f) != Piece::NO_PIECE) {
                    canShortCastle = false;
                }
            }

            // Check that the necessary squares are not seen by enemy pieces
            for (char f = 5; f <= 6 && canShortCastle; f++) {
                Vector necessarySquare(kingRank, f);
                for(Vector& oppSquare : squaresSeenByOpponent) {
                    if (oppSquare == necessarySquare) {
                        canShortCastle = false;
                        break;
                    }
                }
            }

            if (canShortCastle) {
                moves.emplace_back(position, Vector(kingRank, 6), king, SHORT_CASTLE);
            }
        }

        // Long castle
        if (canLongCastle) {
            // Check for no pieces
            char kingRank = king.getStartRank();
            for (char f = 3; f >= 1 && canLongCastle; f--) {
                if (getPiece(kingRank, f) != Piece::NO_PIECE) {
                    canLongCastle = false;
                }
            }

            // Check that the necessary squares are not seen by enemy pieces
            for (char f = 3; f >= 2 && canLongCastle; f--) {
                Vector necessarySquare(kingRank, f);
                for(Vector& oppSquare : squaresSeenByOpponent) {
                    if (oppSquare == necessarySquare) {
                        canLongCastle = false;
                        break;
                    }
                }
            }

            if (canLongCastle) {
                moves.emplace_back(position, Vector(kingRank, 2), king, LONG_CASTLE);
            }
        }
    }
}