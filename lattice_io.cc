#include "lattice_io.h"
#include <vector>
#include <sstream>
#include <stdlib.h>

unsigned int num_words_in_string(std::string path) {
        std::stringstream stream(path);
        std::string word;
        int counter = 0;
        while(stream >> word) {
                counter++;
        };
        return counter;
};

std::vector<std::string> list_files(std::string path) {
        std::vector<std::string> files;
        for( auto &p : fs::directory_iterator(path)) {
                std::string file(p.path());
                files.push_back(file);                
        };                                                                                          
        return files;
};

double timestep(std::string path) { 
        std::stringstream stream(path);
        std::string parameter;
        getline(stream, parameter, ',');
        getline(stream, parameter, ',');
        double dt = atof(parameter.c_str());
        getline(stream, parameter, ',');
        getline(stream, parameter, ',');
        double iter = atof(parameter.c_str());
        return dt*iter; 
};


