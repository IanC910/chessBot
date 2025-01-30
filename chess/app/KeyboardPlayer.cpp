
#include <iostream>
#include <string>

#include "../core/core.hpp"

#include "KeyboardPlayer.hpp"

using namespace Chess;

KeyboardPlayer::KeyboardPlayer() :
    Player()
{}

Move KeyboardPlayer::takeTurn(const Board& board) {
    Chess::MoveCalculator moveCalculator(board);
    std::list<Move> allAvailableMoves;
    moveCalculator.getAllMoves(allAvailableMoves, getColour());
    
    std::string moveString;
    while(true) {
        std::cout << "Type move (E.g. a2a3): ";
        std::cin >> moveString;

        std::cout << "Your move: " << moveString << "\n";

        if (moveString.length() == 4) {
            char startFile  = moveString[0] - 'a';
            char startRank  = moveString[1] - '1';
            char endFile    = moveString[2] - 'a';
            char endRank    = moveString[3] - '1';

            Vector startPos(startRank, startFile);
            Vector endPos(endRank, endFile);

            for (Move& move : allAvailableMoves) {
                if (startPos == move.startPos && endPos == move.endPos) {
                    return move;
                }
            }
        }

        std::cout << "Invalid move. Try again\n";
    }
}
