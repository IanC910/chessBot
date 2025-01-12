
#pragma once

class ChessVector {
public:
    static bool isValid(char rank, char file);

    static const ChessVector INVALID_VEC;

    char rank;
    char file;

    ChessVector();
    ChessVector(char rank, char file);
    ChessVector(const ChessVector& vec);

    bool isValid() const;

    bool equals(const ChessVector& vec) const;
    ChessVector getOpposite() const;
    ChessVector plus(const ChessVector& vec) const;
    ChessVector minus(const ChessVector& vec) const;
    void increaseBy(const ChessVector& vec);
    int dotProduct(const ChessVector& vec);
};