#ifndef UPDATER_H
#define UPDATER_H
#include "system.h"
#include <random>
#include "pcg_random.hpp"

/*
 * Physical variables object
 */
class parameters {																																														                                                
	private:				        
		const static int rn_div = pow(2,20);
		const double Dx;                                                                                            
		const double Dy;                                                                                            
		const double Lx;                                                                                            
		const double Ly;                                                                                            
		const double Cl;
		std::random_device rd;
		pcg32 rng;
       	std::uniform_int_distribution<int> urd;

	public:										                                                                                                              
		parameters(double dx, double dy, double lx, double ly, double cl) : Dx(dx), Dy(dy), Lx(lx), Ly(ly), Cl(cl)
		, rng(rd()), urd(std::uniform_int_distribution<int>(0, rn_div)) {}        
		double random_real();	
		double get_cL() const;
		double get_Dx() const;
		double get_Dy() const;
		double get_Lx() const;
		double get_Ly() const;
};                                                                                                             

angle_lattice update_lattice(const angle_lattice&, const parameters&, double);
angle_lattice update_even(const angle_lattice&, const parameters&, double);
angle_lattice update_odd(const angle_lattice&, const parameters&, double);

double sin_points(const angle_lattice&, int, int, int, int); //sin of difference of two points 
double cos_points(const angle_lattice&, int, int, int, int); //cos of difference of two points

#endif	
