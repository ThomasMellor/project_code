#ifndef UPDATER_H
#define UPDATER_H
#include "system.h"


class parameters {																																															friend lattice update_lattice(lattice&, parameters&, double, double);                                                   
	private:				        
		const double Dx;                                                                                            
		const double Dy;                                                                                            
		const double Lx;                                                                                            
		const double Ly;                                                                                            
	public:										                                                                                                              
		parameters(double dx, double dy, double lx, double ly) : Dx(dx), Dy(dy), Lx(lx), Ly(ly) {}           
};                                                                                                             
                                                                                                              
lattice update_lattice(lattice&, parameters&, double, double);

double sin_points(lattice&, int, int, int, int);
double cos_points(lattice&, int, int, int, int);

#endif	
