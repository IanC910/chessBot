
#include "game/Game.hpp"
#include "game/KeyboardPlayer.hpp"


int main() {
    Chess::KeyboardPlayer whitePlayer;
    Chess::KeyboardPlayer blackPlayer;

    Chess::Game game(whitePlayer, blackPlayer);
    
    game.play();
}