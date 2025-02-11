
#include <iostream>
#include <fstream>

#include "Game.hpp"

using namespace Chess;

Game::Game(Player& whitePlayer, Player& blackPlayer) :
    whitePlayer(whitePlayer), blackPlayer(blackPlayer)
{
    reset();

    whitePlayer.setColour(WHITE);
    blackPlayer.setColour(BLACK);
}

void Game::reset() {
    board.reset();
    movesCalculated = false;
    boardAnalyzer = BoardAnalyzer(board);

    turnColour = WHITE;

    gameIsOver = false;
    winnerColour = NO_COLOUR;

    moveHistory.clear();
    boardHistory.clear();
    boardHistory.push_back(board);

    std::ofstream logFile(GAME_LOG_FILE_NAME);
    logFile << board.toString() << "\n";
    logFile.close();
}

Colour Game::getTurnColour() const {
    return turnColour;
}

const Board& Game::getBoard() const {
    return board;
}

bool Game::tryNextTurn() {
    if (!movesCalculated) {
        boardAnalyzer.getAllMoves(availableMoves, turnColour);
    }
    movesCalculated = true;

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

    moveHistory.push_back(requestedMove);
    boardHistory.push_back(board);
    std::ofstream logFile(GAME_LOG_FILE_NAME, std::ofstream::app);
    logFile << std::to_string(moveHistory.size()) << ": " << requestedMove.toString() << "\n";
    logFile << board.toString() << "\n";
    logFile.close();

    turnColour = getOppositeColour(turnColour);

    // Check stop conditions
    if (board.hasInsufficientMaterial()) {
        gameIsOver = true;
        return true;
    }

    boardAnalyzer = BoardAnalyzer(board);
    boardAnalyzer.getAllMoves(availableMoves, turnColour);
    if (availableMoves.empty()) {
        gameIsOver = true;

        if(boardAnalyzer.isKingChecked(turnColour)) {
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

const std::list<Move>& Game::getMoveHistory() const {
    return moveHistory;
}

const std::list<Board>& Game::getBoardHistory() const {
    return boardHistory;
}

Move Game::getLastMove() const {
    return moveHistory.back();
}