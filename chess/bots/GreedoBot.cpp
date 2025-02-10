
#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>

#include "GreedoBot.hpp"

Chess::Move GreedoBot::takeTurn(const Chess::Board& board) {
    Chess::BoardAnalyzer boardAnalyzer(board);
    std::list<Chess::Move> availableMoves;
    boardAnalyzer.getAllMoves(availableMoves, getColour());
    if (availableMoves.empty()) {
        return Chess::Move();
    }

    int modifier = 1;
    if (getColour() == Chess::BLACK) {
        modifier = -1;
    }

    std::vector<Chess::Board> possibleBoards;
    possibleBoards.reserve(availableMoves.size());

    std::list<Chess::Move>::iterator moveIt = availableMoves.begin();
    while (moveIt != availableMoves.end()) {
        possibleBoards.emplace_back(board);
        possibleBoards.back().doMove(*moveIt);
        ++moveIt;
    }

    int maxValueIndex = rand() % possibleBoards.size();
    int maxValue = modifier * possibleBoards[maxValueIndex].getMaterialValue();
    for (int i = 0; i < possibleBoards.size(); i++) {
        int value = modifier * possibleBoards[i].getMaterialValue();
        if (value > maxValue) {
            maxValueIndex = i;
            maxValue = value;
        }
    }

    moveIt = availableMoves.begin();
    for (int i = 0; i < maxValueIndex; i++) {
        ++moveIt;
    }

    return *moveIt;
}
