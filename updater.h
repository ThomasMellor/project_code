#ifndef UPDATER_H
#define UPDATER_H
#include "system.h"


class parameters {																																															friend angle_lattice update_lattice(const angle_lattice&, const parameters&, double);                                                   
	private:				        
		const double Dx;                                                                                            
		const double Dy;                                                                                            
		const double Lx;                                                                                            
		const double Ly;                                                                                            
		const double Cl;
	public:										                                                                                                              
		parameters(double dx, double dy, double lx, double ly, double cl) : Dx(dx), Dy(dy), Lx(lx), Ly(ly), Cl(cl) {}           
};                                                                                                             
                                                                                                              
angle_lattice update_lattice(const angle_lattice&, const parameters&, double);

double sin_points(const angle_lattice&, int, int, int, int);
double cos_points(const angle_lattice&, int, int, int, int);

#endif	
