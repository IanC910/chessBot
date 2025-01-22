
#pragma once

#include "Player.hpp"

namespace Chess {

    class KeyboardPlayer : public Player {
    public:
        KeyboardPlayer();

        Move takeTurn(const Board& board, Colour colour) override;
    };

}

