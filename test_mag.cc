#include "system.h"
#include "magnetisation.h"
#include <math.h>
#include "vortex_calculation.h"

int main() {
        angle_lattice lat(8);
        angle_lattice lat2(8);
        for( int i = 0; i < 8; i++) {
                for( int j = 0; j < 8; j++) {
                        lat.set(i, j, i+j +i*6.5);
                        lat2.set(i, j, 2*(i+j)+i*j*3.433 +i*j*j);
                };
        };


lat2.set(0, 0, M_PI*1.2);
                       
//        print(lat);
        print(lat2); 
        vortex_lattice vor_lat(8);
        vortex_lattice vor_lat2(8);
        vor_lat.set_vortex_lattice(lat);
        vor_lat2.set_vortex_lattice(lat2);
        std::cout << "vor_lat" << std::endl;
        print(vor_lat); 
        std::cout << "vor_lat2" << std::endl;
        print(vor_lat2);
        vortex_number vor_num1 =  make_vortex_number(lat);
        vortex_number vor_num2 = make_vortex_number(lat2);
        av_vortex_number av_vor1; 
        av_vor1.add(vor_num2);
        std::cout << vor_num1.get_num_vor() << " " << vor_num1.get_num_anti_vor() << std::endl;
        std::cout << vor_num2.get_num_vor() << " " << vor_num2.get_num_anti_vor() << std::endl;
        std::cout << av_vor1.get_av_vor() << " " << av_vor1.get_av_anti_vor() << std::endl;

        av_vor1.add(vor_num1);
        std::cout << av_vor1.get_av_vor() << " " << av_vor1.get_av_anti_vor() << std::endl;
        av_vor1.add(vor_num2);
                std::cout << av_vor1.get_av_vor() << " " << av_vor1.get_av_anti_vor() << std::endl;

        
        magnetisation mag(lat);
        for(auto &p : mag.components()) {
                std::cout << p << std::endl;
        };
        magnetisation mag2(lat2);
        for(auto &p : mag2.components()) {
                std::cout << p << std::endl;
        };       
        av_magnetisation av_mag2(2);
        av_magnetisation av_mag4(4);
        av_mag2.add(mag).add(mag2);
        av_mag4.add(mag).add(mag2);
        std::cout << "av_mag2: " << av_mag2.get_average() << std::endl;
        std::cout << "av_mag4: " << av_mag4.get_average() << std::endl;
        std::cout << binder_cumulant(av_mag2, av_mag4);
};
