
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

    std::list<Move> allAvailableMoves;
    Board boardCopy(board);
    boardCopy.getAllMoves(allAvailableMoves, colour);
    
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
