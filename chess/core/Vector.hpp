
#pragma once

class Vector {
public:
    static bool isValid(char rank, char file);

    static const Vector INVALID;

    char rank;
    char file;

    Vector();
    Vector(char rank, char file);
    Vector(const Vector& vec);

    bool isValid() const;

    bool equals(const Vector& vec) const;
    bool operator==(const Vector& vec) const;
    bool operator!=(const Vector& vec) const;

    Vector getOpposite() const;

    Vector plus(const Vector& vec) const;
    Vector operator+(const Vector& vec) const;

    Vector minus(const Vector& vec) const;
    Vector operator-(const Vector& vec) const;

    void increaseBy(const Vector& vec);
    void operator+=(const Vector& vec);

    int dotProduct(const Vector& vec);
};