
#pragma once

#include "../core/Player.hpp"

class KeyboardPlayer : public Chess::Player {
public:
    KeyboardPlayer();

    Chess::Move takeTurn(const Chess::Board& board) override;
};

