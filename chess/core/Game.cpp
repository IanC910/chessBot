
#include <iostream>

#include "Game.hpp"

Game::Game(Player& whitePlayer, Player& blackPlayer) :
    whitePlayer(whitePlayer), blackPlayer(blackPlayer), board(true)
{}

Game::Game(Player& whitePlayer, Player& blackPlayer, const Board& startingBoard) :
    whitePlayer(whitePlayer), blackPlayer(blackPlayer), board(startingBoard)
{}

void Game::start() {


    Colour turn = WHITE;

    Player* players[2] = {
        &whitePlayer,
        &blackPlayer
    };

    while (true) {
        std::cout << board.toString();

        std::string colourString = (turn == WHITE) ? "White" : "Black";
        std::cout << colourString << "'s turn\n";

        Move move = players[turn]->takeTurn(board, turn);

        // TODO: validate move

        board.doMove(move);

        turn = (Colour)(1 - turn);
    }
}