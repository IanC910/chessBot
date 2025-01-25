
#include "pch.h"
#include "SequencePlayer.hpp"

SequencePlayer::SequencePlayer(std::list<Chess::Move>& moveSequence) :
    moveSequence(moveSequence)
{
    moveIt = moveSequence.begin();
}

Chess::Move SequencePlayer::takeTurn(const Chess::Board& board, Chess::Colour colour) {
    return *(moveIt++);
}
