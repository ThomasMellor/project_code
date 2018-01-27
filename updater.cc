#include "system.h"
#include "updater.h"
#include <math.h>
#include <random>
#include "pcg_random.hpp"

double sin_points(const angle_lattice&, int, int, int, int);
double cos_points(const angle_lattice&, int, int, int, int);

angle_lattice update_lattice(const angle_lattice& lat, const parameters& par, double dt) {
	if((lat.size() % 2) == 0) {
		angle_lattice new_lat = update_even(lat, par, dt);
		return new_lat;
	} else {
		angle_lattice new_lat = update_odd(lat, par, dt);
		return new_lat;
	};
};

double parameters::random_real() { 
	return ((double) urd(rng)/rn_div) - 0.5;
};

double parameters::get_cL() const {
	return Cl;
};

double parameters::get_Dx() const {
	return Dx;
};

double parameters::get_Dy() const {
	return Dy;
};

double parameters::get_Lx() const {
	return Lx;
};

double parameters::get_Ly() const {
	return Ly;
};

double sin_points(const angle_lattice& lat, int i1, int j1, int i2, int j2) {
	return sin(lat.point(i1, j1) - lat.point(i2, j2));
};

double cos_points(const angle_lattice& lat, int i1, int j1, int i2, int j2) {
	return cos(lat.point(i1, j1) - lat.point(i2, j2));
};

angle_lattice update_even(const angle_lattice& lat, const parameters& par, double dt) {
	
	//std::random_device rd;
	//std::mt19937 rng(rd());

	pcg_extras::seed_seq_from<std::random_device> seed_source;                                                
	pcg32_fast rng(seed_source); 
	
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

			double mid_val = 
				dt*(-par.get_Dx()*(sin_right + sin_left)
				-par.get_Dy()*(sin_up + sin_down)
				-par.get_Lx()/2*(cos_left + cos_right - 2)
				-par.get_Ly()/2*(cos_up + cos_down - 2))
			+sqrtdt*2*M_PI*par.get_cL()*(( (double) urd(rng))/rn_div - 0.5);
			//if(i == 5 && j == 5) {
			//	std::cout << "update val "<< mid_val << std::endl;
			//	std::cout << "           " << lat.point(5,4) << std::endl;
			//	std::cout <<  lat.point(4,5) <<  " " << lat.point(5,5) << " " << lat.point(6,5) << std::endl;
			//	std::cout << "           " << lat.point(5,6) << std::endl;
			//};
			new_lat.set(i, j, ang_mid + mid_val);

			double left_val = ang_left + new_lat.point(i - 1, j) +
                +dt*(-par.get_Dx()*(-sin_left) -par.get_Lx()/2*cos_left + par.get_Lx()+ par.get_Ly())
			   	+sqrtdt*2*M_PI*par.get_cL()*( ((double) urd(rng))/rn_div - 0.5);
			new_lat.set(i - 1, j, left_val);

			double right_val = new_lat.point(i + 1, j) +
				dt*(-par.get_Dx()*(-sin_right) - par.get_Lx()/2*cos_right);
			new_lat.set(i + 1, j, right_val);

			double up_val = new_lat.point(i, j + 1) +
				dt*(-par.get_Dy()*(-sin_up) -par.get_Ly()/2*cos_up);
			new_lat.set(i, j + 1, up_val);

			double down_val = new_lat.point(i, j - 1) +
				dt*(-par.get_Dy()*(-sin_down) - par.get_Ly()/2*cos_down);
			new_lat.set(i, j - 1, down_val);
		};
	};
	return new_lat;
};

angle_lattice update_odd(const angle_lattice& lat, const parameters& par, double dt) {

	std::random_device rd;                                                                                    
	std::mt19937 rng(rd());                                                                                          
	int rn_div = pow(2,20);                                                                                   
	//pcg_extras::seed_seq_from<std::random_device> seed_source;										
	//pcg32_fast rng(seed_source); 
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

			double mid_val = 
				dt*(-par.get_Dx()*(sin_right + sin_left)
				-par.get_Dy()*(sin_up + sin_down)
				-par.get_Lx()/2*(cos_left + cos_right - 2)
				-par.get_Ly()/2*(cos_up + cos_down - 2))
                +sqrtdt*2*M_PI*par.get_cL()*(((double) urd(rng))/rn_div- 0.5);
			new_lat.set(i, j, ang_mid + mid_val);
		};
	};
	return new_lat;
};




