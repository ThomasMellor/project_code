#ifndef VORTEX_CALCULATION_H
#define VORTEX_CALCULATION_H

#include "system.h"

vortex_lattice make_vor_lattice(angle_lattice const&);
int circulation(angle_lattice const&, int, int);
double angle_difference(angle_lattice const&, int, int, int, int);                            

class vortex_number {
	private:
		const unsigned int num_vor;
		const unsigned int num_anti_vor;
	public:
		vortex_number(int n_v, int n_av) : num_vor(n_v), num_anti_vor(n_av) {};
		int get_num_vor() const {return num_vor;}
		int get_num_anti_vor() const {return num_anti_vor;}
};

vortex_number make_vortex_num(angle_lattice const&);
vortex_number make_vortex_number(angle_lattice const& lat);                                                  
#endif
