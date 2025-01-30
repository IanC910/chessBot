
#include <iostream>

#include "Game.hpp"

using namespace Chess;

Game::Game(Player& whitePlayer, Player& blackPlayer) :
    whitePlayer(whitePlayer), blackPlayer(blackPlayer)
{
    reset();

    whitePlayer.setColour(WHITE);
    blackPlayer.setColour(BLACK);
}

Game::Game(Player& whitePlayer, Player& blackPlayer, Board& startingBoard, Colour startingTurnColour) :
    whitePlayer(whitePlayer), blackPlayer(blackPlayer),
    board(startingBoard), turnColour(startingTurnColour),
    moveCalculator(startingBoard)
{
    whitePlayer.setColour(WHITE);
    blackPlayer.setColour(BLACK);
}

void Game::reset() {
    board.reset();
    movesCalculated = false;
    moveCalculator = MoveCalculator(board);

    turnColour = WHITE;

    gameIsOver = false;
    winnerColour = NO_COLOUR;
}

Colour Game::getTurnColour() const {
    return turnColour;
}

const Board& Game::getBoard() const {
    return board;
}

void Game::ensureAvailableMovesAreRecent() {
    if (!movesCalculated) {
        moveCalculator.getAllMoves(availableMoves, turnColour);
    }
    movesCalculated = true;
}

bool Game::tryNextTurn() {
    ensureAvailableMovesAreRecent();

    Player* player = &whitePlayer;
    if (turnColour == BLACK) {
        player = &blackPlayer;
    }

    Move requestedMove = player->takeTurn(board);
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
    moveCalculator = MoveCalculator(board);
    movesCalculated = false;

    turnColour = getOppositeColour(turnColour);

    ensureAvailableMovesAreRecent();

    if (availableMoves.empty()) {
        gameIsOver = true;

        if(moveCalculator.isKingChecked(turnColour)) {
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

void Game::playSimple() {
    reset();

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