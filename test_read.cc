#include <iostream>
#include "system.h"
#include "lattice_io.h"

int main() {
	angle_lattice lat(2);
	lattice_read(lat, "./testdir/testdir1,1.txt");
	for( int i = 0; i < lat.size(); i++) {
		for( int j = 0; j < lat.size(); j++) {
			std::cout << lat.point(i, j) << " ";
		};
		std::cout << std::endl;
	};
};
