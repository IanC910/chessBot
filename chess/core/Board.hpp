
#pragma once

#include "Move.hpp"
#include "Vector.hpp"
#include "Piece.hpp"

namespace Chess {

    class Board {
    public:
        Board();
        Board(const Board& board);

        bool equals(const Board& board) const;
        bool operator==(const Board& board) const;
        bool operator!=(const Board& board) const;
        std::string toString() const;

        Piece getPiece(char rank, char file) const;
        Piece getPiece(Vector position) const;
        void setPiece(char rank, char file, const Piece& piece);
        void setPiece(Vector position, const Piece& piece);

        void clear();
        void reset();

        Vector getPositionOfLastMove() const;
        bool wasLastMoveDoublePawn() const;

        bool canColourShortCastle(Colour colour) const;
        bool canColourLongCastle(Colour colour) const;

        void doMove(const Move& move);

        int getMaterialValue() const;
        bool hasInsufficientMaterial();

        uint64_t getPositionCode();

    private:
        Piece pieces[8][8]; // Row-major (Rank then file)

        Vector positionOfLastMove = Vector::INVALID;
        bool lastMoveWasDoublePawn  = false;

        bool whiteCanShortCastle    = false;
        bool whiteCanLongCastle     = false;

        bool blackCanShortCastle    = false;
        bool blackCanLongCastle     = false;
    };
}