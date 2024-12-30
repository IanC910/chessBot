
#pragma once

#include "Board.hpp"
#include "Player.hpp"

class Game {
public:
    Game(Player& whitePlayer, Player& blackPlayer, Board* startingBoard = nullptr);

    void start();

private:
    Board* board = nullptr;

    Player& whitePlayer;
    Player& blackPlayer;
};

