
#include "chess.hpp"


int main() {
    Chess::KeyboardPlayer whitePlayer;
    Chess::KeyboardPlayer blackPlayer;

    Chess::Game game(whitePlayer, blackPlayer);
    
    game.play();
}