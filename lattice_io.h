#ifndef LATTICE_IO
#define LATTICE_IO
#include <fstream> 
#include <iostream>
#include <sstream>
#include <iterator>
#include <experimental/filesystem>                                                                            

                                                                                                              
int main() {                                                                                                  
	    std::string path = "./testdir";                                                                           
		    for( auto &p : fs::directory_iterator(path)) {                                                            
				        std::cout << p << std::endl;                                                                          
						    };                                                                                                        
}; 



unsigned int countWordsInString(std::string const&);

template <typename T> void lattice_write(lattice<T> const& lat, std::string const& path) {	
	std::ofstream file(path);                                                                         
	for(int j = 0; j < lat.size(); j++) {                                                             
		for(int k = 0; k < lat.size(); k++) {                                                         
			file << lat.point(j, k) << " ";                                                           
		};                                                                                            
		file << std::endl;                                                                            
	};
};

template <typename T> void lattice_read(lattice<T>& lat, std::string const& path) {
	std::ifstream file(path);
	if(!file) {
		std::cerr << "Error opening file" << std::endl;
		exit(1);
	};
	std::string line;
	int line_num = 0;
	getline(file, line);
	if(countWordsInString(line) != lat.size()) {
		std::cerr << "Cannot read data onto lattice as incorrect size. " << std::endl;		
		exit(1);
	};
	write_line(lat, line, line_num);
	
	while(getline(file, line)) {
		line_num++;
		write_line(lat, line, line_num);
	};	
};

template <typename T> void write_line(lattice<T> & lat, std::string const& line, int line_num) {
	int pos_in_line = 0; 
	std::istringstream iss(line);	
	T val;
	while(iss >> val) {
		lat.set(line_num, pos_in_line, val);
		pos_in_line++;
	};	
};

unsigned int countWordsInString(std::string const& str) {
	std::stringstream stream(str);
	std::string word;
	int counter = 0;
	while(stream >> word) {
		counter++;
	};
	return counter;
};



#endif
