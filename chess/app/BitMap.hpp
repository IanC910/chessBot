
#pragma once

#include <string>

class BitMap {
public:
	BitMap(int height, int width, char* map);

	int getHeight();
	int getWidth();
	
	int getBit(int row, int col);

private:
	int height;
	int width;
	char* map;
};