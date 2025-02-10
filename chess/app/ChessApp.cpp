
#include <iostream>
#include <string>
#include <sstream>

#include "BoardDrawer.hpp"
#include "KeyboardPlayer.hpp"

#include "../bots/bots.hpp"

#include "ChessApp.hpp"

void ChessApp::run() {
    // present menu:
    //      start new game
    //  ask for player 1 type
    //  ask for player 2 type
    //  play game

    RandallBot whitePlayer;
    GreedoBot blackPlayer;

    playGame(whitePlayer, blackPlayer);
}

void ChessApp::playGame(Chess::Player& whitePlayer, Chess::Player& blackPlayer) {
    BoardDrawer drawer;

    Chess::Game game(whitePlayer, blackPlayer);

    while (!game.isGameOver()) {
        drawer.drawBoard(game.getBoard());

        std::cout << Chess::getColourName(game.getTurnColour()) << "'s turn\n";

        while (!game.tryNextTurn()) {
            std::cout << "Invalid move. Try again\n";
        }
    }

    drawer.drawBoard(game.getBoard());

    if (game.getWinnerColour() == Chess::NO_COLOUR) {
        std::cout << "\nGame Over by Stalemate.\n";
    }
    else {
        std::cout << "\nGame Over by Checkmate - Winner: "
            << Chess::getColourName(game.getWinnerColour()) << "!\n";
    }
}