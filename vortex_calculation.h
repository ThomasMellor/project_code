#ifndef VORTEX_CALCULATION_H
#define VORTEX_CALCULATION_H

#include "system.h"


int circulation(angle_lattice const&, int, int);
double angle_difference(angle_lattice const&, int, int, int, int);                            

/*
 * Stores the number of vortices and anti vortices in an angle lattice 
 */
class vortex_number {
	private:
		const unsigned int num_vor;
		const unsigned int num_anti_vor;
	public:
		vortex_number(int n_v, int n_av) : num_vor(n_v), num_anti_vor(n_av) {};
		int get_num_vor() const {return num_vor;};
		int get_num_anti_vor() const {return num_anti_vor;};
};

/*
 * Stores average number of vortices and anti vortices as you 
 * 'add' vortex_number objects to it
 */
class av_vortex_number {
        private: 
                double n_vor;
                double n_anti_vor;
                unsigned int averaging_num; 
        public:
                double get_av_vor() const;
                double get_av_anti_vor() const;
                av_vortex_number() : n_vor(0), n_anti_vor(0), averaging_num(0) {};
				av_vortex_number& add(vortex_number const&); // reaverages vortex numbers
				av_vortex_number(int av_num, double n_v, double n_av) : averaging_num(av_num), n_vor(n_v),
				n_anti_vor(n_av) {};
};

vortex_number make_vortex_number(angle_lattice const&);

#endif
