#ifndef MAGNETISATION_H
#define MAGNETISATION_H
#include "system.h"
#include <vector>
#include <map>

std::vector<double> angle_components(double const&); // (cos val, sin val) from val 

std::vector<double> calculate_components(angle_lattice const&); // av angle_components in the lattice

/*
 *  Stores av angle_components in lattice
 */
class magnetisation {
        private:
                std::vector<double> comp;
        public:
                std::vector<double> components() const {return comp;};
                magnetisation(angle_lattice const& lat) : comp(calculate_components(lat)) {};
};

/*
 * Stores the average of the magnitude of the magnetisation to a power  
 */
class av_magnetisation {
        private:
                double total;
                unsigned int averaging_num;
                const int power;  
        public:
			int get_power() const {return power;}
            av_magnetisation(int pow) : power(pow) {}; 
            av_magnetisation& add(magnetisation const&); // reaverages with the addition on object
            double get_average() const;
            av_magnetisation() : power(0), total(0), averaging_num(0) {};
			double get_total() const { return total;};
			double get_averaging_num() const {return averaging_num;};	
			av_magnetisation(int pow, int av_num, double tot) : power(pow), averaging_num(av_num), total(tot) {};	
};

double magnitude_pow(magnetisation const&, int);

double binder_cumulant(av_magnetisation const&, av_magnetisation const&);

std::map<double, double> make_binder_cumulant_map(std::map<double, av_magnetisation>, 
                                                                std::map<double, av_magnetisation>);

void print(magnetisation const&);

#endif

