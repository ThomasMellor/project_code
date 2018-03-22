#ifndef CORRELATION_H
#define CORRELATION_H
#include <map>
#include "system.h"

class av_correlation {
	private:
		double total;
		unsigned int averaging_num;
	public:
		av_correlation& add(double);
		double get_average() const;
		av_correlation() : total(0), averaging_num(0) {};
			
};

#endif
