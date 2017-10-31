#ifndef LATTICE_IO
#define LATTICE_IO
#include <fstream> 
#include <iostream>
template <typename T> void lattice_write(lattice<T>& lat, std::string& path) {	
	std::cout << lat.size();
	std::ofstream file(path);                                                                         
	for(int j = 0; j < lat.size(); j++) {                                                             
		for(int k = 0; k < lat.size(); k++) {                                                         
			file << lat.point(j, k) << " ";                                                           
		};                                                                                            
		file << std::endl;                                                                            
	};
}; 

#endif
