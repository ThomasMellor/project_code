#include <string>
#include <iostream>

int main() {
	std::string line; 
	std::cout << "enter line" << std::endl;
	std::getline(std::cin, line);
	std::cout << line; 
};
