#include "system.h"
#include "updater.h"

int main() {
	angle_lattice lat(2);
	parameters par(1,1,1,1,1);
	angle_lattice lat2 = update_lattice(lat, par, 1);
};
