#include "vortex_calculation.h"
#include <math.h>
/*
vortex_lattice make_vor_lattice(angle_lattice const& lat) {
        vortex_lattice vor_lat(lat.size());
        for(int i = 0; i < lat.size(); i++) {                                                                     
		for(int j = 0; j < lat.size(); j++) {                                                                    
			vor_lat.set(i, j, circulation(lat, i, j));                                                                                     
		};                                                                                                       
	};          
	return vor_lat;
};      
*/


int circulation(angle_lattice const& lat, int i, int j) {
	double total_angle = 0;
   	total_angle += angle_difference(lat, i+1, j, i, j);	
	total_angle += angle_difference(lat, i+1, j+1, i+1, j);
	total_angle += angle_difference(lat, i, j+1, i+1, j+1);
	total_angle += angle_difference(lat, i, j, i, j+1);

	double residual = 1.0e-12;	
	if(total_angle <= -2*M_PI + residual) {
		return -1;
	} else if(total_angle >= 2*M_PI - residual) {
		return 1;
	} else {
		return 0;
	};
};

double angle_difference(angle_lattice const& lat, int i1, int j1, int i2, int j2){
	double dif = lat.point(i1, j1) - lat.point(i2, j2);
	if (dif < -M_PI) {
		dif += 2*M_PI;
	} else if(dif > M_PI) {
		dif -= 2*M_PI;
	};
        return dif;
};	

vortex_number make_vortex_number(angle_lattice const& lat) {
	int num_vor = 0;
	int num_anti_vor = 0;
	for(int i = 0; i < lat.size(); i++) {
		for(int j = 0; j < lat.size(); j++) {
			int circ = circulation(lat, i, j);
			if(circ > 0) {
				num_vor++;
			} else if(circ < 0) {
				num_anti_vor++;
			};	
		};
	};
    return vortex_number(num_vor, num_anti_vor);
};	

av_vortex_number& av_vortex_number::add(vortex_number const& vor) {
        (*this).n_vor += vor.get_num_vor();
        (*this).n_anti_vor += vor.get_num_anti_vor(); 
        (*this).averaging_num++;
        return *this;
};

double av_vortex_number::get_av_vor() const {
	if ((*this).averaging_num == 0) {
		return 0;
	} else {
		return (*this).n_vor/(*this).averaging_num;
	};
};
double av_vortex_number::get_av_anti_vor() const { 
	if ((*this).averaging_num == 0) {
		return 0;
	} else {
		return (*this).n_anti_vor/(*this).averaging_num;
	};
};
