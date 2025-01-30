
#include "MoveCalculator.hpp"

using namespace Chess;

static int sign(int x) {
    return (x > 0) - (x < 0);
}

MoveCalculator::MoveCalculator() {}

MoveCalculator::MoveCalculator(const Board& board) {
    setBoard(board);
}

void MoveCalculator::setBoard(const Board& board) {
    this->board = board;
    colourOfCalculatedChecks = NO_COLOUR;

    findKings();
}

void MoveCalculator::findKings() {
    for (char r = 0; r < 8; r++) {
        for (char f = 0; f < 8; f++) {
            Piece piece = board.getPiece(r, f);
            if (piece.getType() == KING) {
                if (piece.getColour() == WHITE) {
                    whiteKingPos = {r, f};
                }
                else if (piece.getColour() == BLACK) {
                    blackKingPos = {r, f};
                }
            }
        }
    }
}

Vector MoveCalculator::getKingPos(Colour kingColour) const {
    Vector kingPositions[] = {Vector::INVALID, whiteKingPos, blackKingPos};
    return kingPositions[kingColour];
}

Vector MoveCalculator::getPinDirection(Vector position) const {
    Piece piece = board.getPiece(position);
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

        Piece currPiece = board.getPiece(currPos);
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

bool MoveCalculator::isPiecePinned(Vector position) const {
    return getPinDirection(position) != Vector(0, 0);
}

int MoveCalculator::getNumChecks(Colour kingColour) {
    return getPositionsCheckingKing(kingColour).size();
}

const std::list<Vector>& MoveCalculator::getPositionsCheckingKing(Colour kingColour) {
    if(kingColour != colourOfCalculatedChecks) {
        calculateChecks(kingColour);
    }
    return positionsCheckingKing;
}

bool MoveCalculator::isKingChecked(Colour kingColour) {
    return getNumChecks(kingColour) > 0;
}

void MoveCalculator::addSquaresSeenByPiece(std::list<Vector>& squaresSeen, Vector position) const {
    switch (board.getPiece(position).getType()) {
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

void MoveCalculator::getSquaresSeenByPiece(std::list<Vector>& squaresSeen, Vector position) const {
    squaresSeen.clear();
    addSquaresSeenByPiece(squaresSeen, position);
}

void MoveCalculator::addMovesForPiece(std::list<Move>& moves, Vector position) {
    Piece piece = board.getPiece(position);

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

void MoveCalculator::getMovesForPiece(std::list<Move>& moves, Vector position) {
    moves.clear();
    addMovesForPiece(moves, position);
}

void MoveCalculator::getAllMoves(std::list<Move>& moves, Colour playerColour) {
    moves.clear();

    for (int r = 0; r < 8; r++) {
        for (int f = 0; f < 8; f++) {
            Piece piece = board.getPiece(r, f);
            if (piece.getColour() == playerColour) {
                addMovesForPiece(moves, Vector(r, f));
            }
        }
    }
}void MoveCalculator::calculateChecks(Colour kingColour) {
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

    Piece king = board.getPiece(kingPos);
    std::list<Vector> squaresSeen;

    // Pawn checks
    addSquaresSeenByPawn(squaresSeen, kingPos);
    for (Vector& square : squaresSeen) {
        Piece piece = board.getPiece(square);
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
        Piece piece = board.getPiece(square);
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
        Piece piece = board.getPiece(square);
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
        Piece piece = board.getPiece(square);
        if (piece.getColour() == oppositeColour) {
            if (piece.getType() == KNIGHT) {
                positionsCheckingKing.push_back(square);
            }
        }
    }
}

void MoveCalculator::addSquaresSeenByPawn(std::list<Vector>& squaresSeen, Vector position) const {
    if (!position.isValid()) {
        return;
    }

    Piece piece = board.getPiece(position);
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

void MoveCalculator::addSquaresSeenByBishop(std::list<Vector>& squaresSeen, Vector position) const  {
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

            if (board.getPiece(currPos) != Piece::NO_PIECE) {
                break;
            }

            currPos.increaseBy(directions[d]);
        }
    }
}

void MoveCalculator::addSquaresSeenByKnight(std::list<Vector>& squaresSeen, Vector position) const {
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

void MoveCalculator::addSquaresSeenByRook(std::list<Vector>& squaresSeen, Vector position) const {
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

            if (board.getPiece(currPos) != Piece::NO_PIECE) {
                break;
            }

            currPos.increaseBy(direction);
        }
    }
}

void MoveCalculator::addSquaresSeenByQueen(std::list<Vector>& squaresSeen, Vector position) const {
    if (!position.isValid()) {
        return;
    }

    addSquaresSeenByBishop(squaresSeen, position);
    addSquaresSeenByRook(squaresSeen, position);
}

void MoveCalculator::addSquaresSeenByKing(std::list<Vector>& squaresSeen, Vector position) const {
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

void MoveCalculator::filterEndSquaresByCheckRules(std::list<Vector>& endSquares, Vector startPosition) {
    Piece piece = board.getPiece(startPosition);
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

void MoveCalculator::filterEndSquaresByAvailability(std::list<Vector>& endSquares, Vector startPosition) const {
    Piece piece = board.getPiece(startPosition);
    Colour colour = piece.getColour();
    std::list<Vector>::iterator endSquareIt = endSquares.begin();
    while (endSquareIt != endSquares.end()) {
        if (board.getPiece(*endSquareIt).getColour() == colour) {
            endSquareIt = endSquares.erase(endSquareIt);
        }
        else {
            ++endSquareIt;
        }
    }
}

void MoveCalculator::addPawnMoves(std::list<Move>& moves, Vector position) {
    Piece pawn = board.getPiece(position);
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
        if (board.getPiece(*squareIt).getColour() != getOppositeColour(pawnColour)) {
            squareIt = endSquares.erase(squareIt);
        }
        else {
            ++squareIt;
        }
    }

    if (board.getPiece(noAttackEndPos) == Piece::NO_PIECE) {
        endSquares.push_back(noAttackEndPos);

        if (position.rank == pawn.getStartRank()) {
            // Above check implies validity
            Vector doubleNoAttackEndPos = noAttackEndPos;
            doubleNoAttackEndPos.rank += pawn.getForwardDirection();
            if (board.getPiece(doubleNoAttackEndPos) == Piece::NO_PIECE) {
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
    if (board.wasLastMoveDoublePawn()) {
        bool friendlyOnCorrectRank = (position.rank == pawn.getStartRank() + 3 * pawn.getForwardDirection());
        Vector difference = board.getPositionOfLastMove() - position;
        bool enemyOnCorrectSquare = (difference.rank == 0 && abs(difference.file) == 1);
        if (friendlyOnCorrectRank && enemyOnCorrectSquare) {
            enPassantEndPos.rank = position.rank + pawn.getForwardDirection();
            enPassantEndPos.file = board.getPositionOfLastMove().file;
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

void MoveCalculator::addBishopMoves(std::list<Move>& moves, Vector position) {
    Piece bishop = board.getPiece(position);
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

void MoveCalculator::addKnightMoves(std::list<Move>& moves, Vector position) {
    Piece knight = board.getPiece(position);
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

void MoveCalculator::addRookMoves(std::list<Move>& moves, Vector position) {
    Piece rook = board.getPiece(position);
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

void MoveCalculator::addQueenMoves(std::list<Move>& moves, Vector position) {
    addBishopMoves(moves, position);
    addRookMoves(moves, position);
}

void MoveCalculator::addKingMoves(std::list<Move>& moves, Vector position) {
    std::list<Vector> endSquares;
    addSquaresSeenByKing(endSquares, position);
    filterEndSquaresByAvailability(endSquares, position);

    // Find all squares seen by opponent
    // Restrict king from moving to those squares
    // Remove all squares seen by opponent from king's possible end squares

    Piece king = board.getPiece(position);
    Colour kingColour = king.getColour();
    Colour oppositeColour = getOppositeColour(kingColour);

    // Get all squares seen by enemies
    std::list<Vector> squaresSeenByOpponent;
    for (int r = 0; r < 8; r++) {
        for (int f = 0; f < 8; f++) {
            Piece piece = board.getPiece(r, f);
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
    bool canShortCastle = board.canColourShortCastle(kingColour);
    bool canLongCastle  = board.canColourLongCastle(kingColour);

    if (!isKingChecked(kingColour)) {
        // Short castle
        if (canShortCastle) {
            // Check for no pieces
            char kingRank = king.getStartRank();
            for (char f = 5; f <= 6 && canShortCastle; f++) {
                if (board.getPiece(kingRank, f) != Piece::NO_PIECE) {
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
                if (board.getPiece(kingRank, f) != Piece::NO_PIECE) {
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
