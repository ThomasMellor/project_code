#include <string>
#include <iostream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem::v1;

int main() {
	std::string path = "./testdir";
	for( auto &p : fs::directory_iterator(path)) {
		std::cout << p << std::endl;
	};
};
