
#pragma once

#include "../core/Board.hpp"

#include "Player.hpp"

namespace Chess {

    class Game {
    public:
        Game(Player& whitePlayer, Player& blackPlayer);

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
        bool movesCalculated = false;
        std::list<Move> availableMoves;

        Player& whitePlayer;
        Player& blackPlayer;

        Colour turnColour = WHITE;

        bool gameIsOver = false;
        Colour winnerColour = NO_COLOUR;
    };

}

