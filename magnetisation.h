#ifndef MAGNETISATION_H
#define MAGNETISATION_H
#include "system.h"
#include <vector>

std::vector<double> angle_components(double);

class av_magnetisation {
        private:
                std::vector<double> components = {0, 0};
                unsigned int averaging_num = 0;
        public:
};
#endif

