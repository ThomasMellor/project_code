#include "system.h"
#include "updater.h"
#include <math.h>
#include <random>

/*
class parameters {
	private: 
		friend lattice update_lattice(lattice, parameters);	
		double Dx;
		double Dy;
		double Lx;
		double Ly;

		double getDx { return Dx };
		double getDy { return Dy };
		double getLx { return Lx };
		double getLy { return Ly };
	public:
		parameters(double dx, double dy, double lx, double ly) : Dx(dx), Dy(dy), Lx(lx), Ly(ly) {};
}
*/

double sin_points(lattice&, int, int, int, int);
double cos_points(lattice&, int, int, int, int);
lattice update_lattice(lattice& lat, parameters& par, double dt, double cL) {	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-0.5,0.5);
	
	double sqrtdt = sqrt(dt);  
	lattice new_lat(lat.size());	
	int N = lat.size();
	for(int i=0; i < N; i++) {
		for(int j=0; j < N; j++) {
			double val = lat.point(i,j)+ 
					  dt*(-par.Dx*( sin_points(lat, i, j, i+1, j) + sin_points(lat, i, j, i-1, j) )
						 -par.Dy*( sin_points(lat, i, j, i, j+1) + sin_points(lat, i, j, i, j-1) )
						 -par.Lx/2*( cos_points(lat, i, j, i+1, j) + cos_points(lat, i, j, i-1, j) -2)
						 -par.Ly/2*( cos_points(lat, i, j, i, j+1) + cos_points(lat, i, j, i, j-1) -2))
						 +sqrtdt*2*M_PI*cL*dis(gen);
			new_lat.set(i,j,val);	
		}
	}
	return new_lat;
};

double sin_points(lattice& lat, int i1, int j1, int i2, int j2) {
	return sin(lat.point(i1, j1) - lat.point(i2, j2));
};

double cos_points(lattice& lat, int i1, int j1, int i2, int j2) {
	return cos(lat.point(i1, j1) - lat.point(i2, j2));
};






