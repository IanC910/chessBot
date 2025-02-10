
#include <cstdlib>
#include <iostream>
#include <list>

#include "RandallBot.hpp"

Chess::Move RandallBot::takeTurn(const Chess::Board& board) {
    Chess::BoardAnalyzer boardAnalyzer(board);
    std::list<Chess::Move> availableMoves;
    boardAnalyzer.getAllMoves(availableMoves, getColour());

    int index = rand() % availableMoves.size();
    std::list<Chess::Move>::iterator moveIt = availableMoves.begin();
    for (int i = 0; i < index; i++) {
        ++moveIt;
    }

    return *moveIt;
}