#include "magnetisation.h"
#include "system.h"
#include <iostream>
#include <math.h>

int main() {
	angle_lattice lat(2);
	angle_lattice lat2(2);
	for(int i = 0; i < lat.size(); i++) {
		for(int j = 0; j < lat.size(); j++) {
			lat.set(i, j, M_PI/2);
		};
	};
	magnetisation mag(lat);
	magnetisation mag2(lat2);
	std::cout << mag.components()[0] << " " << mag.components()[1] << std::endl;
	std::cout << mag2.components()[0] << " " << mag2.components()[1] << std::endl;
	av_magnetisation av_mag2(2);
	av_magnetisation av_mag4(2);
	std::cout << mag.components()[0] << " " << mag.components()[1] << std::endl;
	av_mag2.add(mag2);
	av_mag2.add(mag2);
	std::cout << av_mag2.get_average() << std::endl;
//	std::cout << av_mag4.get_average() << std::endl;
//	std::cout << binder_cumulant(av_mag2,av_mag4);
};
