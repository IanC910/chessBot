
#include <iostream>

#include "Game.hpp"

using namespace Chess;

Game::Game(Player& whitePlayer, Player& blackPlayer) :
    whitePlayer(whitePlayer), blackPlayer(blackPlayer)
{}

Game::Game(Player& whitePlayer, Player& blackPlayer, const Board& startingBoard) :
    whitePlayer(whitePlayer), blackPlayer(blackPlayer)
{}

void Game::init() {
    board.setToStartingBoard();

    Colour turnColour = WHITE;
    Colour winnerColour = NO_COLOUR;
}

Colour Game::getCurrentTurn() const {
    return turnColour;
}

void Game::updateAvailableMoves() {
    if (!movesCalculated) {
        board.getAllMoves(availableMoves, turnColour);
    }
    movesCalculated = true;
}

bool Game::tryNextTurn() {
    updateAvailableMoves();

    Player* player = &whitePlayer;
    if (turnColour == BLACK) {
        player = &blackPlayer;
    }

    Move requestedMove = player->takeTurn(board, turnColour);
    bool moveIsValid = false;
    for (Move& move : availableMoves) {
        if (requestedMove == move) {
            moveIsValid = true;
            break;
        }
    }

    if(!moveIsValid) {
        return false;
    }

    board.doMove(requestedMove);
    turnColour = getOppositeColour(turnColour);
    movesCalculated = false;

    updateAvailableMoves();
    if (availableMoves.empty()) {
        gameIsOver = true;

        if(board.isKingChecked(turnColour)) {
            winnerColour = getOppositeColour(turnColour);
        }
    }

    return true;
}

bool Game::isGameOver() const {
    return gameIsOver;
}

Colour Game::getWinnerColour() const {
    return winnerColour;
}

void Game::play() {
    init();

    while (!isGameOver()) {
        std::cout << "\n" << board.toString() << "\n";

        std::cout << getColourName(turnColour) << "'s turn\n";

        while (!tryNextTurn()) {
            std::cout << "Invalid move. Try again\n";
        }
    }

    if (getWinnerColour() == NO_COLOUR) {
        std::cout << "\nGame Over by Stalemate.\n";
    }
    else {
        std::cout << "\nGame Over by Checkmate - Winner: " << getColourName(getWinnerColour()) << "!\n";
    }
}