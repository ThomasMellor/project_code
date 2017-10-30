#ifndef LATTICE_H
#define LATTICE_H

#include <vector>    
#include <iostream>    
#include <math.h>    
    
    
template<typename T> class lattice{    
	private:    
		const unsigned int N;    
		std::vector<std::vector<T>> lattice_points = 
			std::vector<std::vector<T>>(N,std::vector<T>(N));
		template <typename R> R mod(R,R);    
	public:    
		int getN() { return N; };
		lattice(unsigned int s) : N(s) {}    	
		lattice(const lattice&);
		lattice& operator=(const lattice&);
		~lattice() {};

		T point(int, int);    
		virtual void set(int, int, T);    
		size_t size() const;
};    

class angle_lattice : public lattice<double> {
	public:
		virtual void set(int, int, double);
};
#endif

