
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
    board.setToStartingBoard();

    Colour turnColour = WHITE;
    Colour winnerColour = NO_COLOUR;

    while (true) {
        std::cout << board.toString();

        Player* player = &whitePlayer;
        if (turnColour == BLACK) {
            player = &blackPlayer;
        }

        std::list<Move> allMovesAvailable;
        board.getAllMoves(allMovesAvailable, turnColour);
        if (allMovesAvailable.empty()) {
            // Either checkmate or stalemate
            if (board.isKingChecked(turnColour)) {
                winnerColour = getOppositeColour(turnColour);
            }

            break;
        }

        std::string colourString = (turnColour == WHITE) ? "White" : "Black";
        std::cout << colourString << "'s turn\n";

        bool moveIsValid = false;
        while (!moveIsValid) {
            Move requestedMove = player->takeTurn(board, turnColour);
            for (Move& move : allMovesAvailable) {
                if (requestedMove == move) {
                    moveIsValid = true;
                    board.doMove(requestedMove);
                    break;
                }
            }

            if (!moveIsValid) {
                std::cout << "Invalid Move. Try again\n";
            }
        }

        turnColour = getOppositeColour(turnColour);
    }

    if (winnerColour == NO_COLOUR) {
        std::cout << "Stalemate\n";
    }
    else {
        std::string colourString = (winnerColour == WHITE) ? "White" : "Black";
        std::cout << "Winner: " << colourString << "!\n";
    }
}