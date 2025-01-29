
#include <vector>

#include "AlphaBot.hpp"

Chess::Move AlphaBot::takeTurn(const Chess::Board& board) {
    std::list<Chess::Move> availableMoves;
    Chess::Board boardCopy(board);
    boardCopy.getAllMoves(availableMoves, getColour());

    int modifier = 1;
    if (getColour() == Chess::BLACK) {
        modifier = -1;
    }

    std::vector<Chess::Board*> possibleBoards;
    possibleBoards.reserve(availableMoves.size());

    std::list<Chess::Move>::iterator moveIt = availableMoves.begin();
    while (moveIt != availableMoves.end()) {
        Chess::Board* newBoard = new Chess::Board(board);
        newBoard->doMove(*moveIt);
        possibleBoards.push_back(newBoard);
        ++moveIt;
    }

    int maxValueIndex = 0;
    int maxValue = modifier * possibleBoards[maxValueIndex]->getMaterialValue();
    for (int i = 1; i < possibleBoards.size(); i++) {
        int value = modifier * possibleBoards[i]->getMaterialValue();
        if (value > maxValue) {
            maxValueIndex = i;
            maxValue = value;
        }
    }

    for (int i = 0; i < possibleBoards.size(); i++) {
        delete possibleBoards[i];
    }

    moveIt = availableMoves.begin();
    for (int i = 0; i < maxValueIndex; i++) {
        ++moveIt;
    }

    return *moveIt;
}
