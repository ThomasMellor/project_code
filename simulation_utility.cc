#include "simulation_utility.h"

void check_dir(std::string& dir) {
        while(!check_dir_exists(dir)) {
                std::cout << "Directory does not exist. Please try again:" << std::endl;
                getline(std::cin, dir);
        };
};
