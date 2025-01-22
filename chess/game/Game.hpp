
#pragma once

#include "../core/Board.hpp"

#include "Player.hpp"

namespace Chess {

    class Game {
    public:
        Game(Player& whitePlayer, Player& blackPlayer);
        Game(Player& whitePlayer, Player& blackPlayer, const Board& startingBoard);

        void start();

    private:
        Board board;

        Player& whitePlayer;
        Player& blackPlayer;
    };

}

