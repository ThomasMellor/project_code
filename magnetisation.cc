#include "magnetisation.h"
#include <iostream> 
#include <math.h>

av_magnetisation& av_magnetisation::add(magnetisation const& mag) {
        int num = (*this).averaging_num;
        double old_ave = (*this).average;
        (*this).average = old_ave*num + magnitude_pow(mag, (*this).power);  
        (*this).averaging_num++;
        return *this;
};

std::vector<double> angle_components(double const& val) {
        std::vector<double> comps = {cos(val), sin(val)};
        return comps;
};

std::vector<double> calculate_components(angle_lattice const& lat) {
        std::vector<double> comp = {0, 0};
        for(int i = 0; i < lat.size(); i++) {
                for(int j = 0; j < lat.size(); j++) {
                        std::vector<double> added_comps = angle_components(lat.point(i, j));
                        for(int k = 0; comp.size(); k++) {
                                comp[k] += added_comps[k];
                        }; 
                };
        };
        for(int i = 0; i < comp.size(); i++) {
                comp[i] = comp[i]/(lat.size()*lat.size());
        };
        return comp;
};

double magnitude_pow(magnetisation const& mag, int n) {
        double val;
        for(int i = 0; i < mag.components().size(); i++) {
                val += pow(mag.components()[i], n);
        };
        return val; 
};

double binder_cumulant(av_magnetisation const& av_mag_2, av_magnetisation const& av_mag_4) {
        if(av_mag_2.get_power() != 2 && av_mag_4.get_power() !=4) {
                std::cerr << "Error. The powers in the magnetisations are not correct" << std::endl;
                exit(1);
        };
        return 2 - av_mag_2.get_average()/av_mag_4.get_average();
};


