#ifndef SIMULATION_UTILITY_H 
#define SIMULATION_UTILITY_H
#include <iostream>
#include <sstream>
#include <vector>
#include <string> 
#include "lattice_io.h"
/*
template <typename T> bool value_check(std::string line, T&val) { 
        std::istringstream is {line}; 
        if((is >> val) && !(is >> line)){
                return true;
        } else {
                return false;
        };
};

template <typename T> void value_save(std::string name, T& val) {                                                                  
        std::cout << name << ": ";      

        std::string line;
        while(std::getline(std::cin, line)){
                std::istringstream is {line};
                if(value_check(line, val)){
                        break;
                };
                std::cerr << "Invalid input. Please try again: ";
        };
};

template <typename T> bool check_positive_sign(T& val) {
        if(val > 0) {
                return true;
        } else {
                return false;
        };
};
*/

void check_dir(std::string&);

bool check_files_exist(std::vector<std::string>);



#endif
