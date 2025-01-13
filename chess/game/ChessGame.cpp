
#include <iostream>

#include "ChessGame.hpp"

ChessGame::ChessGame(Player& whitePlayer, Player& blackPlayer) :
    whitePlayer(whitePlayer), blackPlayer(blackPlayer), board(true)
{}

ChessGame::ChessGame(Player& whitePlayer, Player& blackPlayer, const Board& startingBoard) :
    whitePlayer(whitePlayer), blackPlayer(blackPlayer), board(startingBoard)
{}

void ChessGame::start() {


    Colour turn = WHITE;

    while (true) {
        std::cout << board.toString();

        std::string colourString = (turn == WHITE) ? "White" : "Black";
        std::cout << colourString << "'s turn\n";

        Player* player = &whitePlayer;
        if (turn == BLACK) {
            player = &blackPlayer;
        }

        Move move = player->takeTurn(board, turn);

        // TODO: validate move

        board.doMove(move);

        // TODO: Check for win condition

        turn = getOppositeColour(turn);
    }
}