#ifndef LATTICE_H
#define LATTICE_H

#include <vector>    
#include <iostream>    
#include <math.h>    
    
    
class lattice{    
	private:    
		const int N;    
		std::vector<std::vector<double> > lattice_points = 
			std::vector<std::vector<double> >(N,std::vector<double>(N));
		template <typename T> T mod(T,T);    
	public:    
		lattice(unsigned int s) : N(s) {}    	
		lattice(const lattice&);
		lattice& operator=(const lattice&);
		~lattice() {};

		double point(int, int);    
		void set(int, int, double);    
		int size() const;
};    



#endif    
    
    

