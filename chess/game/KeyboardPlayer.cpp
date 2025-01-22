
#include <iostream>
#include <string>

#include "../core/Board.hpp"
#include "../core/Move.hpp"
#include "../core/Vector.hpp"

#include "KeyboardPlayer.hpp"

using namespace Chess;

KeyboardPlayer::KeyboardPlayer() :
    Player()
{}

Move KeyboardPlayer::takeTurn(const Board& board, Colour colour) {
    setColour(colour);
    
    std::string moveString;

    while(true) {
        std::cout << "Type move: ";
        std::cin >> moveString;

        std::cout << "Your move: " << moveString << "\n";

        if (moveString.length() == 4) {
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

    char startFile  = moveString[0] - 'a';
    char startRank  = moveString[1] - '1';
    char endFile    = moveString[2] - 'a';
    char endRank    = moveString[3] - '1';
    
    Move move(
        Vector(startRank, startFile),
        Vector(endRank, endFile),
        board.getPiece(startRank, startFile)
    );

    return move;
}
