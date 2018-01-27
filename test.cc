#include "system.h"
#include "updater.h"
#include "initial_condition.h"

int main() {
	angle_lattice lat = disordered(3);
	print(lat);	
	parameters par(1,2,3,4,0);
	angle_lattice lat2 = update_lattice(lat, par, 1);
	print(lat2);
};
