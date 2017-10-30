#include <iostream>
#include "system.h"
#include "updater.h"

int main() {
	angle_lattice lat(2);
	
	lat.size();
	for(int i=0; i<2; i++) {
		for(int j=0; j<2; j++) {
			lat.set(i, j, i+j);	
		};
	};
	for(int i=0; i<2; i++) {                                                                                  
		for(int j=0; j<2; j++) {                                                                              
			lat.point(i,j);
		};
		std::cout << std::endl;
	};
	std::cout << std::endl;

	angle_lattice lat_new(2);	
	lat_new = lat;
		
		
	parameters param(1,1,1,1,0);
	angle_lattice new_lat = update_lattice(lat, param, 1);
	for(int i=0; i<2; i++) {
		for(int j=0; j<2; j++) {
			std::cout << new_lat.point(i,j) << " ";
		};
		std::cout << std::endl;
	};
};
