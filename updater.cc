#include "system.h"
#include "updater.h"
#include <math.h>
#include <random>
#include "pcg_random.hpp"

double sin_points(const angle_lattice&, int, int, int, int);
double cos_points(const angle_lattice&, int, int, int, int);

angle_lattice update_lattice(const angle_lattice& lat, parameters& par, double dt) {
//	if((lat.size() % 2) == 0) {
		angle_lattice new_lat = update_odd(lat, par, dt);
		return new_lat;
//	} else {
//		angle_lattice new_lat = update_odd(lat, par, dt);
//		return new_lat;
//	};
};

double parameters::random_real() {
	return ((double) urd(rng)/rn_div) - 0.5;
};

double sin_points(const angle_lattice& lat, int i1, int j1, int i2, int j2) {
	return sin(lat.point(i1, j1) - lat.point(i2, j2));
};

double cos_points(const angle_lattice& lat, int i1, int j1, int i2, int j2) {
	return cos(lat.point(i1, j1) - lat.point(i2, j2));
};

angle_lattice update_even(const angle_lattice& lat, parameters& par, double dt) {
	
	std::random_device rd;                                                                                
	pcg32_fast rng(rd());
	int rn_div = pow(2,20); 	
	std::uniform_int_distribution<int> urd(0, rn_div);	
	
	int N = lat.size();
	angle_lattice new_lat(N);
	double sqrtdt = sqrt(dt);

	for(int j = 0; j < N; j++) {
		int i = 0;
		if ( (j % 2) != 0) {
			i = 1;
		};
		
		for(i; i < N; i+=2) {

			double ang_mid = lat.point(i, j);
			double ang_up = lat.point(i, j + 1);
			double ang_down = lat.point(i, j - 1);
			double ang_left = lat.point(i - 1, j);
			double ang_right = lat.point(i + 1, j);

			double sin_left = sin(ang_mid - ang_left);
			double sin_right = sin(ang_mid - ang_right);
			double sin_up = sin(ang_mid - ang_up);
			double sin_down = sin(ang_mid - ang_down);

			double cos_left = cos(ang_mid - ang_left);
			double cos_right = cos(ang_mid - ang_right);
			double cos_up = cos(ang_mid - ang_up);
			double cos_down = cos(ang_mid - ang_down);

			double mid_val = ang_mid +
				dt*(-par.Dx*(sin_right + sin_left)
				-par.Dy*(sin_up + sin_down)
				-par.Lx/2*(cos_left + cos_right - 2)
				-par.Ly/2*(cos_up + cos_down - 2));
			+sqrtdt*2*M_PI*par.Cl*urd(rng)/rn_div;
			new_lat.set(i, j, mid_val);

			double left_val = ang_left + new_lat.point(i - 1, j) +
                +dt*(-par.Dx*(-sin_left) -par.Lx/2*cos_left + par.Lx + par.Ly);
			   	+sqrtdt*2*M_PI*par.Cl*urd(rng)/rn_div;
			new_lat.set(i - 1, j, left_val);

			double right_val = new_lat.point(i + 1, j) +
				dt*(-par.Dx*(-sin_right) - par.Lx/2*cos_right);
			new_lat.set(i + 1, j, right_val);

			double up_val = new_lat.point(i, j + 1) +
				dt*(-par.Dy*(-sin_up) -par.Ly/2*cos_up);
			new_lat.set(i, j + 1, up_val);

			double down_val = new_lat.point(i, j - 1) +
				dt*(-par.Dy*(-sin_down) - par.Ly/2*cos_down);
			new_lat.set(i, j - 1, down_val);
		};
	};
	return new_lat;
};

angle_lattice update_odd(const angle_lattice& lat, parameters& par, double dt) {

	std::random_device rd;                                                                                    
	std::mt19937 rng(rd());                                                                                          
	int rn_div = pow(2,20);                                                                                   
	std::uniform_int_distribution<int> urd(0, rn_div);              

	double sqrtdt = sqrt(dt);
	int N = lat.size();
	angle_lattice new_lat(N);

	for(int i = 0; i < N; ++i) {
		for(int j = 0; j < N; ++j) {

			double ang_mid = lat.point(i, j);
			double ang_up = lat.point(i, j + 1);
			double ang_down = lat.point(i, j - 1);
			double ang_left = lat.point(i - 1, j);
			double ang_right = lat.point(i + 1, j);

			double sin_left = sin(ang_mid - ang_left);
			double sin_right = sin(ang_mid - ang_right);
			double sin_up = sin(ang_mid - ang_up);
			double sin_down = sin(ang_mid - ang_down);

			double cos_left = cos(ang_mid - ang_left);
			double cos_right = cos(ang_mid - ang_right);
			double cos_up = cos(ang_mid - ang_up);
			double cos_down = cos(ang_mid - ang_down);

			double mid_val = ang_mid +
				dt*(-par.Dx*(sin_right + sin_left)
				-par.Dy*(sin_up + sin_down)
				-par.Lx/2*(cos_left + cos_right - 2)
				-par.Ly/2*(cos_up + cos_down - 2))
                +sqrtdt*2*M_PI*par.Cl*urd(rng)/rn_div;
			new_lat.set(i, j, mid_val);
		};
	};
	return new_lat;
};




