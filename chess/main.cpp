
#include "core/Game.hpp"
#include "core/KeyboardPlayer.hpp"


int main() {
    KeyboardPlayer whitePlayer;
    KeyboardPlayer blackPlayer;

    Game game(whitePlayer, blackPlayer);
    
    game.start();
}