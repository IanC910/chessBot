
#include <iostream>
#include <string>

#include "log.hpp"

void log(std::string context, std::string message) {
	std::string line = "[" + context + "] " + message;
	std::cout << line << std::endl;
}