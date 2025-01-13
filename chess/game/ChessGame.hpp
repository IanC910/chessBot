
#pragma once

#include "../core/Board.hpp"

#include "Player.hpp"

class ChessGame {
public:
    ChessGame(Player& whitePlayer, Player& blackPlayer);
    ChessGame(Player& whitePlayer, Player& blackPlayer, const Board& startingBoard);

    void start();

private:
    Board board;

    Player& whitePlayer;
    Player& blackPlayer;
};

