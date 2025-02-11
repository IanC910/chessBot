
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

    GreedoBot whitePlayer;
    TreeWizardBot blackPlayer(3);
    bool drawBoard = false;

    playGame(whitePlayer, blackPlayer, drawBoard);
}

void ChessApp::playGame(Chess::Player& whitePlayer, Chess::Player& blackPlayer, bool drawBoard) {
    BoardDrawer drawer;

    Chess::Game game(whitePlayer, blackPlayer);

    while (!game.isGameOver()) {
        if(drawBoard) {
            drawer.drawBoard(game.getBoard());
        }

        std::cout << Chess::getColourName(game.getTurnColour()) << "'s turn\n";

        while (!game.tryNextTurn()) {
            std::cout << "Invalid move. Try again\n";
        }

        std::cout << "Move: " << game.getLastMove().toString() << "\n";
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