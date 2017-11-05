#ifndef MAGNETISATION_H
#define MAGNETISATION_H
#include "system.h"
#include <vector>
#include <unordered_map>

std::vector<double> angle_components(double const&);

std::vector<double> calculate_components(angle_lattice const&);

class magnetisation {
        private:
                std::vector<double> comp;
        public:
                std::vector<double> components() const {return comp;};
                magnetisation(angle_lattice const& lat) : comp(calculate_components(lat)) {};
};

class av_magnetisation {
        private:
                double average = 0;
                unsigned int averaging_num = 0;
                const int power;
        public:
                int get_power() const {return power;}
                av_magnetisation(int pow) : power(pow) {}; 
                av_magnetisation& add(magnetisation const&);
                double get_average() const {return average;};
                av_magnetisation() : power(0) {};
};

double magnitude_pow(magnetisation const&, int);

double binder_cumulant(av_magnetisation const&, av_magnetisation const&);

std::unordered_map<double, double> make_binder_cumulant_map(std::unordered_map<double, av_magnetisation>, 
                                                                std::unordered_map<double, av_magnetisation>);

#endif

