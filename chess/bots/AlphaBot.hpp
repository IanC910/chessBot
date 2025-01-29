
#pragma once

#include "../chess.hpp"

class AlphaBot : public Chess::Player {
public:
    Chess::Move takeTurn(const Chess::Board& board) override;
};

