
#include "Player.hpp"

Player::Player() {}

Colour Player::getColour() {
    return colour;
}

void Player::setColour(Colour colour) {
    this->colour = colour;
}
