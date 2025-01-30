
#include "Player.hpp"

using namespace Chess;

Player::Player() {}

Colour Player::getColour() const {
    return colour;
}

void Player::setColour(Colour colour) {
    this->colour = colour;
}
