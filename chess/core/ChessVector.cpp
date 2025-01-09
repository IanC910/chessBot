
#include "ChessVector.hpp"

const ChessVector ChessVector::INVALID_VEC(-128, -128);

bool ChessVector::isValid(char rank, char file) {
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

ChessVector ChessVector::add(const ChessVector& vec) const {
    return ChessVector(rank + vec.rank, file + vec.file);
}

ChessVector ChessVector::subtract(const ChessVector& vec) const {
    return ChessVector(rank - vec.rank, file - vec.file);
}

void ChessVector::increaseBy(const ChessVector& vec) {
    rank += vec.rank;
    file += vec.file;
}