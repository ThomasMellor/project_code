#include "lattice_io.h"
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <utility> 

bool check_dir_exists(std::string path){ 
        struct stat sb;
        if(stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)){
                return true;
        } else {
                return false;
        };       
};



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

angle_lattice angle_lattice_from_path(std::string const& path) {
        std::ifstream file(path);
        if(!file) {
                std::cerr << "Error opening file" << std::endl;
                exit(1);
        };
        std::string line;
        int line_num = 0;
        getline(file, line);
        angle_lattice lat(num_words_in_string(line));
        write_line(lat, line, line_num); 
        while(getline(file, line)) {
                line_num++;
                write_line(lat, line, line_num);
        };
        return lat;
};

angle_lattice empty_angle_lattice_from_path(std::string const& path) {
        std::ifstream file(path);
        if(!file) {
                std::cerr << "Error opening file" << std::endl;
                exit(1);
        };
        std::string line;
        getline(file, line);
        angle_lattice lat(num_words_in_string(line));
        return lat;
};

std::unordered_map<double, av_vortex_number> make_vortex_map(std::vector<std::string> const& files) {
        angle_lattice lat = empty_angle_lattice_from_path(files[0]);        
        std::unordered_map<double, av_vortex_number> vor_map; 
        for(std::string const& st : files) {
                double time = timestep(st);
                lattice_read(lat, st);
                vortex_number vor_num = make_vortex_number(lat);
                vor_map[time].add(vor_num); 
        };
        return vor_map;
};

std::unordered_map<double, av_magnetisation> make_magnetisation_map(std::vector<std::string> const& files, int pow) {
        angle_lattice lat = empty_angle_lattice_from_path(files[0]);
        std::unordered_map<double, av_magnetisation> mag_map;
        for(std::string const& st : files) {
                double time = timestep(st);
                lattice_read(lat, st);
                magnetisation mag(lat);
                if(mag_map.count(time) != 0) {
                       av_magnetisation av_mag(pow);
                       mag_map.insert(std::make_pair(time, av_mag));
                       mag_map.at(time).add(mag);      
                } else {
                        mag_map.at(time).add(mag);
                };
        };
        return mag_map;
};

