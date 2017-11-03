#include <vector>
#include <iostream>
#include <math.h>
#include "system.h"
#include <stdexcept>


void angle_lattice::set(int x, int y, double ang) {
	lattice<double>::set(x, y, mod(ang,2*M_PI));
};

angle_lattice::angle_lattice(int N) : lattice<double>(N) {};

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

vortex_lattice::vortex_lattice(int N) : lattice<int>(N) {};
