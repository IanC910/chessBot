
#pragma once

#include "../core/core.hpp"

class GreedoBot : public Chess::Player {
public:
    Chess::Move takeTurn(const Chess::Board& board) override;
};

