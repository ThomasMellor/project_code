#include <iostream>
#include <fstream>
#include <string>

int main() {
	std::string dir("./testdir");
	std::string path(dir + "/" +  "hello.txt");                          
	std::cout << path << std::endl;
	std::ofstream file(path);
	file << "stuff";
};	
