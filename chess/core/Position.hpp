
#pragma once

class Position {
public:
    static bool isValid(char rank, char file);
    static bool isValid(const Position& position);

    char rank : 4;
    char file : 4;

    Position();
    Position(char rank, char file);
    Position(const Position& position);

    bool isValid() const;

    bool equals(const Position& position) const;
};