#include "system.h"
#include "updater.h"
#include <math.h>
#include <random>

double sin_points(angle_lattice&, int, int, int, int);
double cos_points(angle_lattice&, int, int, int, int);

angle_lattice update_lattice(angle_lattice& lat, parameters& par, double dt) {	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-0.5,0.5);
	
	double sqrtdt = sqrt(dt);  
	angle_lattice new_lat(lat.size());	
	int N = lat.size();
	for(int i=0; i < N; i++) {
		for(int j=0; j < N; j++) {
			double val = lat.point(i,j)+ 
					  dt*(-par.Dx*( sin_points(lat, i, j, i+1, j) + sin_points(lat, i, j, i-1, j) )
						 -par.Dy*( sin_points(lat, i, j, i, j+1) + sin_points(lat, i, j, i, j-1) )
						 -par.Lx/2*( cos_points(lat, i, j, i+1, j) + cos_points(lat, i, j, i-1, j) -2)
						 -par.Ly/2*( cos_points(lat, i, j, i, j+1) + cos_points(lat, i, j, i, j-1) -2))
						 +sqrtdt*2*M_PI*par.Cl*dis(gen);
			new_lat.set(i,j,val);	
		}
	}
	return new_lat;
};

double sin_points(angle_lattice& lat, int i1, int j1, int i2, int j2) {
	return sin(lat.point(i1, j1) - lat.point(i2, j2));
};

double cos_points(angle_lattice& lat, int i1, int j1, int i2, int j2) {
	return cos(lat.point(i1, j1) - lat.point(i2, j2));
};






