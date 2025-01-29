
#pragma once

#include "../chess.hpp"

class AlphaBot : Chess::Player {


    Chess::Move takeTurn(const Chess::Board& board) override;


};

