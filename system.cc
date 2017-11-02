#include <vector>
#include <iostream>
#include <math.h>
#include "system.h"
#include <stdexcept>

void angle_lattice::set(int x, int y, double ang) {
	lattice<double>::set(x, y, mod(ang,2*M_PI));
};

angle_lattice::angle_lattice(int N) : lattice<double>(N) {};

void vortex_lattice::set(int x, int y, int charge) {
	lattice<int>::set(x, y, charge);
};

vortex_lattice::vortex_lattice(int N) : lattice<int>(N) {};
