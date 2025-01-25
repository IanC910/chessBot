
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

void Game::doNextTurn() {
    Player* player = &whitePlayer;
    if (turnColour == BLACK) {
        player = &blackPlayer;
    }

    std::list<Move> allAvailableMoves;
    board.getAllMoves(allAvailableMoves, turnColour);
    if (allAvailableMoves.empty()) {
        gameIsOver = true;

        // Either checkmate or stalemate
        if (board.isKingChecked(turnColour)) {
            winnerColour = getOppositeColour(turnColour);
        }

        return;
    }

    std::string colourString = (turnColour == WHITE) ? "White" : "Black";
    std::cout << colourString << "'s turn\n";

    while (true) {
        Move requestedMove = player->takeTurn(board, turnColour);
        for (Move& move : allAvailableMoves) {
            if (requestedMove == move) {
                board.doMove(requestedMove);
                turnColour = getOppositeColour(turnColour);
                break;
            }
        }
        
        std::cout << "Invalid move. Try again\n";
    }
}

bool Game::isGameOver() const {
    return gameIsOver;
}

Colour Game::getWinnerColour() const {
    return winnerColour;
}

void Game::play() {
    init();

    while (true) {
        std::cout << board.toString();

        doNextTurn();

        if (isGameOver()) {
            break;
        }
    }

    if (winnerColour == NO_COLOUR) {
        std::cout << "Game Over by Stalemate.\n";
    }
    else {
        std::string colourString = (winnerColour == WHITE) ? "White" : "Black";
        std::cout << "Game Over by Checkmate - Winner: " << colourString << "!\n";
    }
}