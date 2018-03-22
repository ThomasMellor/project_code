#include "lattice_io.h"
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <utility> 
#include <iomanip>

bool check_dir_exists(std::string path){ 
        struct stat sb;
        if(stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)){
                return true;
        } else {
                return false;
        };       
};

void file_error_message(std::string file) {
	std::cout << "Error opening file " + file << std::endl;	
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
    double dt = deltat(path);
	int iter = iteration(path);
	return dt*iter; 
};

double deltat(std::string path) {
    std::stringstream stream(path);
    std::string parameter;
    getline(stream, parameter, ',');
    getline(stream, parameter, ',');
    double dt = atof(parameter.c_str());
	return dt;
};

int iteration(std::string path) {
	std::string parameter;
	std::stringstream stream(path);
	getline(stream, parameter, ',');
    getline(stream, parameter, ',');
	getline(stream, parameter, ',');
    getline(stream, parameter, ',');
   	int iter = atof(parameter.c_str());
	return iter;
};

double simulation_number(std::string path) {
	std::stringstream stream(path);
	std::string parameter;
	getline(stream, parameter, ',');
	getline(stream, parameter, ',');
	getline(stream, parameter, ',');
	getline(stream, parameter, ',');
	getline(stream, parameter, ',');
	getline(stream, parameter, ',');
	int sim_num = atof(parameter.c_str());
	return sim_num;	
};

angle_lattice angle_lattice_from_path(std::string const& path) {
        std::ifstream file(path);
        if(!file) {
			file_error_message(path); 
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
			file_error_message(path); 
            exit(1);
        };
        std::string line;
        getline(file, line);
        angle_lattice lat(num_words_in_string(line));
        return lat;
};

vortex_lattice empty_vortex_lattice_from_path(std::string const& path) {
	std::ifstream file(path);
	if(!file) {
		file_error_message(path);	
		exit(1);
	};
	std::string line;
	getline(file, line);
	vortex_lattice lat(num_words_in_string(line));
	return lat;
};


std::map<double, av_vortex_number> make_vortex_map(std::vector<std::string> const& files) {
        angle_lattice lat = empty_angle_lattice_from_path(files[0]);        
        std::map<double, av_vortex_number> vor_map; 
        for(std::string const& st : files) {
                double time = timestep(st);
                lattice_read(lat, st);
                vortex_number vor_num = make_vortex_number(lat);
                vor_map[time].add(vor_num); 
        };
        return vor_map;
};

std::map<int, av_correlation> make_correlation_map(std::vector<std::string> const& files, double time) {
	angle_lattice lat = empty_angle_lattice_from_path(files[0]);
	std::map<int, av_correlation> av_cor_map;
	bool not_in = true;
	for(std::string const& st : files) {
		if(time != timestep(st)) {
			continue;
			not_in = false;
		};
		lattice_read(lat, st);
		double angle_0 = lat.point(0,0);
		for(int i = 1; i < lat.size()/2; i++) {
			av_cor_map[i].add(cos(angle_0 - lat.point(i,0)));
		};	
	};
	if(not_in == true) {
		std::cerr << "Timestep not part of results!" << std::endl;
		exit(1);
	};
	return av_cor_map;
};


std::vector<std::map<double, av_magnetisation>> make_magnetisation_map(std::vector<std::string> const& files, std::initializer_list<int> pow_args) {
    angle_lattice lat = empty_angle_lattice_from_path(files[0]);
	std::vector<std::map<double, av_magnetisation>> mag_map_list(pow_args.size());
    for(std::string const& st : files) {
        double time = timestep(st);
        lattice_read(lat, st);
        magnetisation mag(lat);
		for(size_t i = 0; i < pow_args.size(); i++) {
			if(mag_map_list[i].count(time) == 0) {
                av_magnetisation av_mag(pow_args.begin()[i]);
                mag_map_list[i].insert(std::make_pair(time, av_mag));
                mag_map_list[i].at(time).add(mag); // [] does not work as no default contructor for av_mag    
			} else {
                mag_map_list[i].at(time).add(mag);
			};
		};
	};
    return mag_map_list;
};

void write_binder_cumulant(std::map<double, double> const& binder_map, std::string const& dir, std::string const& name) {
        std::string path = dir + "/" + name;         
        std::ofstream file(path);
        for(std::map<double, double>::const_iterator iter = binder_map.cbegin(); iter != binder_map.cend(); iter++) { 
                double time = (*iter).first;
                double mag = (*iter).second;    
                file << time << " " << mag << std::endl;
        };
};

void write_magnetisation(std::map<double, av_magnetisation> const& mag_map, std::string const& dir, std::string const& name) {
	std::string path = dir + "/" + name;
	std::ofstream file(path);
	for(std::map<double, av_magnetisation>::const_iterator iter = mag_map.cbegin(); iter != mag_map.cend(); iter++){
		double time = (*iter).first;
		double mag = (*iter).second.get_average();
		file << time << " " << mag << std::endl;		
	};
};

void write_correlation(std::map<int, av_correlation> const& cor_map, std::string const& dir, std::string const& name) {
	std::string path = dir + "/" + name;
	std::ofstream file(path);
	for(std::map<int, av_correlation>::const_iterator iter = cor_map.cbegin(); iter != cor_map.cend(); iter++){
		int distance = (*iter).first;
		double cor = (*iter).second.get_average();
		file << distance << " " << cor << std::endl;		
	};
};


std::map<double, av_magnetisation> mag_averaged(std::string const& path_1, std::string const& path_2, int power, int runs_1, int runs_2) {
	std::ifstream file_1(path_1);
	std::ifstream file_2(path_2);
	if(!file_1) {
		file_error_message(path_1); 
        exit(1);
    };
	if(!file_2) {
		file_error_message(path_2); 
        exit(1);
    };
	std::string line_1;
	std::string line_2;

	std::map<double, av_magnetisation> mag_map;
	while(getline(file_1, line_1) && getline(file_2, line_2)) {
		std::stringstream line_1_s(line_1);
		std::stringstream line_2_s(line_2);
		double time_1, time_2;
		line_1_s >> time_1;
		line_2_s >> time_2;
		if(time_1 != time_2) {
			std::cerr << "Error. Times in the files are different" << std::endl;
			exit(1);
		};
		double av_1, av_2;
		line_1_s >> av_1;
		line_2_s >> av_2;	
		av_magnetisation av_mag(power, runs_1 + runs_2, av_1*runs_1 + av_2*runs_2);
		std::cout << av_mag.get_averaging_num() << std::endl;
		mag_map.insert(std::make_pair(time_1, av_mag));	
	};
	return mag_map;	
};

std::map<double, av_vortex_number> vortex_averaged(std::string const& path_1, std::string const& path_2, int runs_1, int runs_2) {
	std::ifstream file_1(path_1);
	std::ifstream file_2(path_2);
	if(!file_1) {
		file_error_message(path_1); 
        exit(1);
    };
	if(!file_2) {
		file_error_message(path_2); 
        exit(1);
    };
	std::string line_1;
	std::string line_2;
	
	std::map<double, av_vortex_number> vor_map;
	while(getline(file_1, line_1) && getline(file_2, line_2)) {
		std::stringstream line_1_s(line_1);
		std::stringstream line_2_s(line_2);
		double time_1, time_2;
		line_1_s >> time_1;
		line_2_s >> time_2;
		if(time_1 != time_2) {
			std::cerr << "Error. Times in the files are different" << std::endl;
			exit(1);
		};
		std::cout << time_1 << " " << time_2 << std::endl;
		double nv_1, nv_2, nav_1, nav_2;
		line_1_s >> nv_1;
		line_2_s >> nv_2;
		line_1_s >> nav_1;
		line_2_s >> nav_2;	
		av_vortex_number av_vor(runs_1 + runs_2, nv_1*runs_1 + nv_2*runs_2, nav_1*runs_1 + nav_2*runs_2);
		vor_map.insert(std::make_pair(time_1, av_vor));	
	};
	return vor_map;	
};


void write_vortex_number(std::map<double, av_vortex_number> const& vortex_map, std::string const& dir, std::string const& name) {
        std::string path = dir + "/" + name;
        std::ofstream file(path);
        for(std::map<double, av_vortex_number>::const_iterator iter = vortex_map.cbegin(); iter != vortex_map.cend(); iter++) {
                double time = (*iter).first;
                file << time << " " << std::fixed << std::setprecision(8)  << (*iter).second.get_av_vor() << " " << (*iter).second.get_av_anti_vor() << std::endl;
        };
};
   
