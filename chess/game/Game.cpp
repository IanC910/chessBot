
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

        std::list<Move> allAvailableMoves;
        board.getAllMoves(allAvailableMoves, turnColour);
        if (allAvailableMoves.empty()) {
            // Either checkmate or stalemate
            if (board.isKingChecked(turnColour)) {
                winnerColour = getOppositeColour(turnColour);
            }

            break;
        }

        std::string colourString = (turnColour == WHITE) ? "White" : "Black";
        std::cout << colourString << "'s turn\n";

        Move requestedMove;
        while (true) {
            requestedMove = player->takeTurn(board, turnColour);
            bool moveIsValid = false;
            for (Move& move : allAvailableMoves) {
                if (requestedMove == move) {
                    moveIsValid = true;
                    break;
                }
            }

            if (moveIsValid) {
                break;
            }
            else {
                std::cout << "Invalid move. Try again\n";
            }
        }

        board.doMove(requestedMove);
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