
#include "Position.hpp"

Position::Position() {}

Position::Position(char rank, char file) {
	this->rank = rank;
	this->file = file;
}

Position::Position(const Position& position) {
	this->rank = position.rank;
	this->file = position.file;
}

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

bool Position::isValid() {
	return isValid(this->rank, this->file);
}

bool Position::equals(const Position& position) {
	return (
		this->rank == position.rank &&
		this->file == position.file
	);
}