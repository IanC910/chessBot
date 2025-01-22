
#include <iostream>

#include "Game.hpp"

using namespace Chess;

Game::Game(Player& whitePlayer, Player& blackPlayer) :
    whitePlayer(whitePlayer), blackPlayer(blackPlayer)
{}

Game::Game(Player& whitePlayer, Player& blackPlayer, const Board& startingBoard) :
    whitePlayer(whitePlayer), blackPlayer(blackPlayer)
{}

void Game::start() {


    Colour turn = WHITE;

    while (true) {
        std::cout << board.toString();

        std::string colourString = (turn == WHITE) ? "White" : "Black";
        std::cout << colourString << "'s turn\n";

        Player* player = &whitePlayer;
        if (turn == BLACK) {
            player = &blackPlayer;
        }

        Move move = player->takeTurn(board, turn);

        // TODO: validate move

        board.doMove(move);

        // TODO: Check for win condition

        turn = getOppositeColour(turn);
    }
}