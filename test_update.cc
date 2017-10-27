#include <iostream>
#include "system.h"
#include "updater.h"

int main() {
	lattice lat(2);


	for(int i=0; i<2; i++) {
		for(int j=0; j<2; j++) {
			lat.set(i, j, i+j);	
		};
	};
	for(int i=0; i<2; i++) {                                                                                  
		for(int j=0; j<2; j++) {                                                                              
			std::cout << lat.point(i,j) << " ";                                                           
		};
		std::cout << std::endl;
	};
	std::cout << std::endl;

	
	parameters param(1,1,1,1);
	lattice new_lat = update_lattice(lat, param, 1, 0);
	for(int i=0; i<2; i++) {
		for(int j=0; j<2; j++) {
			std::cout << new_lat.point(i,j) << " ";
		};
		std::cout << std::endl;
	};
};
