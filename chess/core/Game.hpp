
#pragma once

#include <string>

#include "Board.hpp"
#include "BoardAnalyzer.hpp"

#include "Player.hpp"

namespace Chess {

    class Game {
    public:
        Game(Player& whitePlayer, Player& blackPlayer);

        void reset();
        Colour getTurnColour() const;
        const Board& getBoard() const;
        bool tryNextTurn();

        bool isGameOver() const;
        Colour getWinnerColour() const;

        void playSimple();

        const std::list<Move>& getMoveHistory() const;
        const std::list<Board>& getBoardHistory() const;

    private:
        Board board;

        Player& whitePlayer;
        Player& blackPlayer;

        Colour turnColour = WHITE;

        bool gameIsOver = false;
        Colour winnerColour = NO_COLOUR;

        BoardAnalyzer moveCalculator;
        bool movesCalculated = false;
        std::list<Move> availableMoves;

        std::list<Move> moveHistory;
        std::list<Board> boardHistory;

        const std::string GAME_LOG_FILE_NAME = "game.log";
    };
}

