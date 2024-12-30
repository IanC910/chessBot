
#include <iostream>
#include <string>

#include "Board.hpp"
#include "Move.hpp"
#include "Position.hpp"

#include "KeyboardPlayer.hpp"

KeyboardPlayer::KeyboardPlayer() :
    Player()
{}

Move KeyboardPlayer::takeTurn(const Board& board, Colour colour) {
    setColour(colour);

    std::string colourString = (getColour() == WHITE) ? "White" : "Black";
    std::cout << colourString << "'s turn\n";
    
    std::string startPos;
    std::string endPos;

    while(true) {
        std::cout << "Type move: ";
        std::cin >> startPos >> endPos;

        std::cout << "Your move: " << startPos << " " << endPos << "\n";

        if (startPos.length() == 2 && endPos.length() == 2) {
            char confirmation;
            std::cout << "Confirm [y]: ";
            std::cin >> confirmation;
            if (std::tolower(confirmation) == 'y') {
                break;
            }
        }
        else {
            std::cout << "Invalid move\n";
        }
    }

    char startFile  = startPos[0] - 'a';
    char startRank  = startPos[1] - '1';
    char endFile    = endPos[0] - 'a';
    char endRank    = endPos[1] - '1';
    
    Move move(
        Position(startRank, startFile),
        Position(endRank, endFile),
        board.getPiece(startRank, startFile)
    );

    return move;
}
