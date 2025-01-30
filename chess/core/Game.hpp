
#pragma once

#include "Board.hpp"
#include "MoveCalculator.hpp"

#include "Player.hpp"

namespace Chess {

    class Game {
    public:
        Game(Player& whitePlayer, Player& blackPlayer);
        Game(Player& whitePlayer, Player& blackPlayer, Board& startingBoard, Colour startingTurnColour);

        void reset();
        Colour getTurnColour() const;
        const Board& getBoard() const;
        void ensureAvailableMovesAreRecent();
        bool tryNextTurn();

        bool isGameOver() const;
        Colour getWinnerColour() const;

        void playSimple();

    private:
        Board board;

        Player& whitePlayer;
        Player& blackPlayer;

        Colour turnColour = WHITE;

        bool gameIsOver = false;
        Colour winnerColour = NO_COLOUR;

        MoveCalculator moveCalculator;
        bool movesCalculated = false;
        std::list<Move> availableMoves;
    };

}

