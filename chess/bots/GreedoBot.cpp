
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

    for (Chess::Move& move : availableMoves) {
        possibleBoards.emplace_back(board);
        possibleBoards.back().doMove(move);
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

    std::list<Chess::Move>::iterator moveIt = availableMoves.begin();
    for (int i = 0; i < maxValueIndex; i++) {
        ++moveIt;
    }

    return *moveIt;
}
