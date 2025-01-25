
#include <iostream>

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

    Chess::Game game(whitePlayer, blackPlayer);
    game.init();

    while (!game.isGameOver()) {
        Chess::Board board = game.getBoard();
        std::cout << "\n" << board.toString();

        std::cout << Chess::getColourName(game.getTurnColour()) << "'s turn\n";

        while (!game.tryNextTurn()) {
            std::cout << "Invalid move. Try again\n";
        }
    }

    if (game.getWinnerColour() == Chess::NO_COLOUR) {
        std::cout << "\nGame Over by Stalemate.\n";
    }
    else {
        std::cout << "\nGame Over by Checkmate - Winner: "
            << Chess::getColourName(game.getWinnerColour()) << "!\n";
    }
}