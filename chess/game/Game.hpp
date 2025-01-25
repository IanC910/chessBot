
#pragma once

#include "../core/Board.hpp"

#include "Player.hpp"

namespace Chess {

    class Game {
    public:
        Game(Player& whitePlayer, Player& blackPlayer);
        Game(Player& whitePlayer, Player& blackPlayer, const Board& startingBoard);

        void init();
        Colour getCurrentTurn() const;
        void updateAvailableMoves();
        bool tryNextTurn();

        bool isGameOver() const;
        Colour getWinnerColour() const;

        void play();

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

