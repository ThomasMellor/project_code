#include "lattice_io.h"
#include "system.h"
#include "magnetisation.h"
#include "vortex_calculation.h"
#include <iostream>


int main() {

	std::cout << "Please type in the directory in which to save the Binder data:" << std::endl;
	std::string write_binder_dir;
	std::cin >> write_binder_dir;
	
	std::cout << "Please type in the first file for the magnetisation with power 2:" << std::endl;
	std::string mag_2_file_1;
	std::cin >> mag_2_file_1;

	std::cout << "Please type in the second file for the magnetisation with power 2:" << std::endl;
	std::string mag_2_file_2;
	std::cin >> mag_2_file_2;

	std::cout << "Please type in the first file for the magnetisation with power 4:" << std::endl;
	std::string mag_4_file_1;
	std::cin >> mag_4_file_1;
	std::cout << "Please type in the second file for the magnetisation with power 4:" << std::endl;
	std::string mag_4_file_2;
	std::cin >> mag_4_file_2;
	
	std::cout << "Please type in the directory in which to save the vortex data:" << std::endl;               
	std::string write_vor_dir;                                                                                
	std::cin >> write_vor_dir;

	std::cout << "Please type in the first file for the vortices:" <<std::endl;
	std::string vortex_file_1;
	std::cin >> vortex_file_1;
	std::cout << "Please type in the second file for the vortices:" <<std::endl;
	std::string vortex_file_2;
	std::cin >> vortex_file_2;

	std::cout << "Please type in the number of runs for the first file set:" << std::endl;
	std::cout << "Please type in the number of runs for the second file set:" << std::endl;
	int runs_1, runs_2;
	std::cin >> runs_1;
	std::cin >> runs_2;

	
	std::cout << "Please type in the name of the Binder file you want to save this:" << std::endl;
	std::string binder_file;
	std::cin >> binder_file;

	std::cout << "Please type in the name of the vortex file you want to save this:" << std::endl;
	std::string vor_file;
	std::cin >> vor_file;

	std::map<double, av_magnetisation> mag_map_2 = mag_averaged(write_binder_dir + "/" + mag_2_file_1, write_binder_dir + "/" +  mag_2_file_2, 2, runs_1, runs_2);
	std::map<double, av_magnetisation> mag_map_4 = mag_averaged(write_binder_dir + "/" +  mag_4_file_1, write_binder_dir + "/" +  mag_4_file_2, 4, runs_1, runs_2);
	std::map<double, av_vortex_number> vor_map = vortex_averaged(write_vor_dir + "/" +  vortex_file_1, write_vor_dir + "/" + vortex_file_2, runs_1, runs_2);	
	 
    std::map<double, double> binder_cumulant_map = make_binder_cumulant_map(mag_map_2, mag_map_4);
	write_binder_cumulant(binder_cumulant_map, write_binder_dir, binder_file);
	write_magnetisation(mag_map_2, write_binder_dir, "mag_2" + binder_file);
	write_magnetisation(mag_map_4, write_binder_dir, "mag_4" + binder_file);
	
	write_vortex_number(vor_map, write_vor_dir, vor_file);	
};
