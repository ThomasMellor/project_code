#include <vector>
#include <iostream>
#include <math.h>
#include "system.h"
#include <stdexcept>
#include "vortex_calculation.h"


void angle_lattice::set(int x, int y, double ang) {
	lattice<double>::set(x, y, mod(ang,2*M_PI));
};

/*
 * Constructor
 */
angle_lattice::angle_lattice(int N) : lattice<double>(N) {};

/*
 * Sets (x,y) to charge 'charge' and updates the number of charges accordingly
 */
void vortex_lattice::set(int x, int y, int charge) {
	int pre_charge = this -> point(x, y);
	int added_charge = sign(charge);	
	lattice<int>::set(x, y, added_charge);
	if(pre_charge == 0 && charge == 0) {
		return; 
	}	
	else if(pre_charge != 0 && charge != 0){
		n_vor += added_charge;
		n_anti_vor += pre_charge;
	}
	else if (pre_charge == 0) { 
		if(charge > 0) {
			n_vor++;
		} else {
			n_anti_vor++;	
		};
	} else {
		if(pre_charge > 0) {
			n_vor--;
		} else {
			n_anti_vor--;
		};		
	};	
};

/*
 * Constructor
 */
vortex_lattice::vortex_lattice(int N) : lattice<int>(N) {};

/*
 *Returns a vortex lattice set from the angle lattice lat
 */
vortex_lattice& vortex_lattice::set_vortex_lattice(angle_lattice const& lat) {
        if((*this).size() != lat.size()){
                std::cerr << "Vortex lattice and angle lattice not the same size. Error. " << std::endl;
                exit(1);      
        };
        for(int i = 0; i < lat.size(); i++) {
                for(int j = 0; j < lat.size(); j++) {
                        (*this).set(i, j, circulation(lat, i, j));                                                                              
                };
        };
        return *this;
};
