#ifndef VORTEX_CALCULATION_H
#define VORTEX_CALCULATION_H

#include "system.h"

int circulation(angle_lattice const&, int, int);
double angle_difference(angle_lattice const&, int, int, int, int);                            

class vortex_number {
	private:
		const unsigned int num_vor;
		const unsigned int num_anti_vor;
	public:
		vortex_number(int n_v, int n_av) : num_vor(n_v), num_anti_vor(n_av) {};
		int get_num_vor() const {return num_vor;};
		int get_num_anti_vor() const {return num_anti_vor;};
};

class av_vortex_number {
        private: 
                double av_vor = 0;
                double av_anti_vor = 0;
                unsigned int averaging_num = 0; 
        public:
                double get_av_vor() const {return av_vor;};
                double get_av_anti_vor() const {return av_anti_vor;};
                av_vortex_number& add(vortex_number const&);
};

vortex_number make_vortex_number(angle_lattice const&);
#endif
