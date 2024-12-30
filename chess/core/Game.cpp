
#include <iostream>

#include "Game.hpp"

Game::Game(Player& whitePlayer, Player& blackPlayer, Board* startingBoard) :
    whitePlayer(whitePlayer), blackPlayer(blackPlayer), board(startingBoard)
{
    if (board == nullptr) {
        board = Board::createStartingBoard();
    }
}

void Game::start() {


    Colour turn = WHITE;

    Player* players[2] = {
        &whitePlayer,
        &blackPlayer
    };

    while (true) {
        std::cout << board->toString();

        Move move = players[turn]->takeTurn(*board, turn);

        board->doMove(move);

        turn = (Colour)(1 - turn);
    }
}