
#include <iostream>
#include <string>
#include <sstream>

#include "BoardDrawer.hpp"

#include "ChessApp.hpp"

void ChessApp::run() {
    // present menu:
    //      start new game
    //  ask for player 1 type
    //  ask for player 2 type
    //  play game

    playGame();
}

void ChessApp::playGame() {
    Chess::KeyboardPlayer whitePlayer;
    Chess::KeyboardPlayer blackPlayer;
    BoardDrawer graphics;

    Chess::Game game(whitePlayer, blackPlayer);
    game.init();

    while (!game.isGameOver()) {
        graphics.drawBoard(game.getBoard());


        std::cout << Chess::getColourName(game.getTurnColour()) << "'s turn\n";

        while (!game.tryNextTurn()) {
            std::cout << "Invalid move. Try again\n";
        }
    }

    graphics.drawBoard(game.getBoard());

    if (game.getWinnerColour() == Chess::NO_COLOUR) {
        std::cout << "\nGame Over by Stalemate.\n";
    }
    else {
        std::cout << "\nGame Over by Checkmate - Winner: "
            << Chess::getColourName(game.getWinnerColour()) << "!\n";
    }
}