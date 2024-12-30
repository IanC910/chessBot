
#include <iostream>
#include <string>

#include "debug.hpp"

void log(std::string context, std::string message) {
	std::string line = "[" + context + "] " + message;
	std::cout << line << std::endl;
}