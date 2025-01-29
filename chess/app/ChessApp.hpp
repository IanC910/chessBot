
#pragma once

#include "../chess.hpp"

class ChessApp {
public:
    void run();

private:

    void playGame(Chess::Player& whitePlayer, Chess::Player& blackPlayer);

};

