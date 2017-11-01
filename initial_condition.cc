#include "initial_condition.h"
#include <math.h>
#include <random> 
#include <iostream>

angle_lattice disordered(int N) {
	std::random_device rd;                                                                                    
    std::mt19937 gen(rd());                                                                                   
	std::uniform_real_distribution<> dis(0,2*M_PI); 
	
	angle_lattice lat(N);
	for(int i = 0; i < lat.size(); i++) {
		for(int j = 0; j < lat.size(); j++) {
			double val = dis(gen);
			lat.set(i, j, val);
		};
	};
	return lat;
};	
