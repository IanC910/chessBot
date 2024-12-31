
#include "Position.hpp"

bool Position::isValid(char rank, char file) {
	return (
		rank >= 0 &&
		rank <= 7 &&
		file >= 0 &&
		file <= 7
	);
}

bool Position::isValid(const Position& position) {
	return isValid(position.rank, position.file);
}

Position::Position() :
	rank(0), file(0)
{}

Position::Position(char rank, char file) :
	rank(rank), file(file)
{}

Position::Position(const Position& position) :
	rank(position.rank), file(position.file)
{}

bool Position::isValid() const {
	return isValid(this->rank, this->file);
}

bool Position::equals(const Position& position) const {
	return (
		this->rank == position.rank &&
		this->file == position.file
	);
}