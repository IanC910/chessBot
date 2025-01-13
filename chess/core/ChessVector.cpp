
#include "ChessVector.hpp"

const ChessVector ChessVector::INVALID_VEC(-128, -128);

inline bool ChessVector::isValid(char rank, char file) {
	return (
		rank >= 0 &&
		rank <= 7 &&
		file >= 0 &&
		file <= 7
	);
}

ChessVector::ChessVector() :
	rank(0), file(0)
{}

ChessVector::ChessVector(char rank, char file) :
	rank(rank), file(file)
{}

ChessVector::ChessVector(const ChessVector& vec) :
	rank(vec.rank), file(vec.file)
{}

bool ChessVector::isValid() const {
	return isValid(this->rank, this->file);
}

bool ChessVector::equals(const ChessVector& vec) const {
	return (
		this->rank == vec.rank &&
		this->file == vec.file
	);
}

bool ChessVector::operator==(const ChessVector& vec) const {
    return equals(vec);
}

bool ChessVector::operator!=(const ChessVector& vec) const {
    return !equals(vec);
}

ChessVector ChessVector::getOpposite() const {
    return ChessVector(-rank, -file);
}

ChessVector ChessVector::plus(const ChessVector& vec) const {
    return ChessVector(rank + vec.rank, file + vec.file);
}

ChessVector ChessVector::operator+(const ChessVector& vec) const {
    return plus(vec);
}

ChessVector ChessVector::minus(const ChessVector& vec) const {
    return ChessVector(rank - vec.rank, file - vec.file);
}

ChessVector ChessVector::operator-(const ChessVector& vec) const {
    return minus(vec);
}

void ChessVector::increaseBy(const ChessVector& vec) {
    rank += vec.rank;
    file += vec.file;
}

void ChessVector::operator+=(const ChessVector& vec) {
    increaseBy(vec);
}

int ChessVector::dotProduct(const ChessVector& vec) {
    return rank * vec.rank + file * vec.file;
}