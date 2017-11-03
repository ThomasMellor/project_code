#include <string>
#include <iostream>
#include "lattice_io.h"


int main() {
        std::vector<std::string> files = list_files("./testdir");
        for(std::string& file : files) {
                std::cout << timestep(file) << std::endl;
        };
};       
