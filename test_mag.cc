#include "system.h"
#include "magnetisation.h"

int main() {
        angle_lattice lat(2);
        angle_lattice lat2(2);
        for( int i = 0; i < 2; i++) {
                for( int j = 0; j < 2; j++) {
                        lat.set(i, j, i+j);
                        lat2.set(i, j, 2*(i+j));
                };
        };       
        print(lat);
        print(lat2); 
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
