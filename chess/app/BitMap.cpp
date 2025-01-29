
#include "BitMap.hpp"

BitMap::BitMap(int height, int width, char* map) {
	this->height = height;
	this->width = width;
	this->map = map;
}

int BitMap::getHeight() {
	return height;
}

int BitMap::getWidth() {
	return width;
}

int BitMap::getBit(int row, int col) {
	return map[row * width + col];
}