#include <random>
#include <iostream>
#include "math.h"
#include "pcg_extras.hpp"
#include "pcg_random.hpp"
int main() {
	//pcg_extras::seed_seq_from<std::random_device> seed_source;
	//pcg32 rng(seed_source);
	std::random_device rd;
	std::mt19937 rng(rd());
	int rn_div = pow(2,20);
    std::uniform_real_distribution<double> urd(0,1);                                                        
	for(int i = 0; i < 1000; i++) {
		//double div = ((double) urd(rng)) /rn_div;
		std::cout << 2*M_PI*(urd(rng)  - 0.5) << std::endl;
	};
};

