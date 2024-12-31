
#pragma once

#include "Board.hpp"
#include "Player.hpp"

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

