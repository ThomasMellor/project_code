#include "correlation.h"
#include <math.h>

double av_correlation::get_average() const {
	if(averaging_num == 0) {
		return 0;
	} else {
		return total/averaging_num;
	};
};

av_correlation& av_correlation::add(double val) {
	averaging_num++;
	total += val;
	return *this;
};

