
#include "Vector.hpp"

const Vector Vector::INVALID(-128, -128);

inline bool Vector::isValid(char rank, char file) {
	return (
		rank >= 0 &&
		rank <= 7 &&
		file >= 0 &&
		file <= 7
	);
}

Vector::Vector() :
	rank(0), file(0)
{}

Vector::Vector(char rank, char file) :
	rank(rank), file(file)
{}

Vector::Vector(const Vector& vec) :
	rank(vec.rank), file(vec.file)
{}

bool Vector::isValid() const {
	return isValid(this->rank, this->file);
}

bool Vector::equals(const Vector& vec) const {
	return (
		this->rank == vec.rank &&
		this->file == vec.file
	);
}

bool Vector::operator==(const Vector& vec) const {
    return equals(vec);
}

bool Vector::operator!=(const Vector& vec) const {
    return !equals(vec);
}

Vector Vector::getOpposite() const {
    return Vector(-rank, -file);
}

Vector Vector::plus(const Vector& vec) const {
    return Vector(rank + vec.rank, file + vec.file);
}

Vector Vector::operator+(const Vector& vec) const {
    return plus(vec);
}

Vector Vector::minus(const Vector& vec) const {
    return Vector(rank - vec.rank, file - vec.file);
}

Vector Vector::operator-(const Vector& vec) const {
    return minus(vec);
}

void Vector::increaseBy(const Vector& vec) {
    rank += vec.rank;
    file += vec.file;
}

void Vector::operator+=(const Vector& vec) {
    increaseBy(vec);
}

int Vector::dotProduct(const Vector& vec) {
    return rank * vec.rank + file * vec.file;
}

std::string Vector::toString() {
    std::string vecString = "12";
    vecString[0] = file + 'a';
    vecString[1] = rank + '1';
    return vecString;
}