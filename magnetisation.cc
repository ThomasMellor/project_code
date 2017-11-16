#include "magnetisation.h"
#include <iostream> 
#include <math.h>
#include <map>

av_magnetisation& av_magnetisation::add(magnetisation const& mag) {
        int num = (*this).averaging_num;
        double old_ave = (*this).average;
        (*this).average = ((double) old_ave*num + magnitude_pow(mag, (*this).power))/(num + 1);  
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
                        for(int k = 0; k < comp.size(); k++) {
                                comp[k] += added_comps[k];
                        }; 
                };
        };
        for(int i = 0; i < comp.size(); i++) {
                double val = comp[i]/(lat.size()*lat.size());
                comp[i] = val;
        };
        return comp;
};

double magnitude_pow(magnetisation const& mag, int n) {
        double val = 0;
        for(int i = 0; i < mag.components().size(); i++) {
                val += pow(mag.components()[i], 2);
        };
		double exp = ((double) n)/2;
        return pow(val, exp);
};

double binder_cumulant(av_magnetisation const& av_mag_2, av_magnetisation const& av_mag_4) {
        if(av_mag_2.get_power() !=2 || av_mag_4.get_power() !=4) {
                std::cerr << "Error. The powers in the magnetisations are not correct" << std::endl;
                exit(1);
        };
        return 2 - av_mag_4.get_average()/(pow(av_mag_2.get_average(), 2));
};

std::map<double, double> make_binder_cumulant_map(std::map<double, av_magnetisation> mag2_map, std::map<double, av_magnetisation> mag4_map) {
        if(mag2_map.at(0).get_power() != 2 || mag4_map.at(0).get_power() !=4 ) {
                std::cerr << "Cannot make binder cumulant map as incorrect powers of average magnetisation" << std::endl;
                exit(1); 
        };        
        std::map<double, double> binder_map; 
        for(std::map<double, av_magnetisation>::const_iterator iter = mag2_map.cbegin(); iter != mag2_map.cend(); iter++) {
                double time = iter -> first;
                std::cout << time << " " << mag2_map.at(time).get_average() << " " << mag4_map.at(time).get_average() << std::endl;
                binder_map[time] = binder_cumulant(mag2_map.at(time), mag4_map.at(time));
                std::cout << binder_map[time] << std::endl;
        };
        return binder_map; 
};
