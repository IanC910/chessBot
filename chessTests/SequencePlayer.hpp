
#pragma once

#include "pch.h"

class SequencePlayer : public Chess::Player {
public:
    SequencePlayer(std::list<Chess::Move>& moveSequence);

    Chess::Move takeTurn(const Chess::Board& board) override;

private:
    std::list<Chess::Move>& moveSequence;
    std::list<Chess::Move>::iterator moveIt;
};

