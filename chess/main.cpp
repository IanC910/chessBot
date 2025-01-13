
#include "game/ChessGame.hpp"
#include "game/KeyboardPlayer.hpp"


int main() {
    KeyboardPlayer whitePlayer;
    KeyboardPlayer blackPlayer;

    ChessGame game(whitePlayer, blackPlayer);
    
    game.start();
}