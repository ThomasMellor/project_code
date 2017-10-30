#include <vector>
#include <iostream>
#include <math.h>
#include "system.h"
#include <stdexcept>

/*
template <typename T> T mod(T,T);

class lattice{
	private:
		const int N;
		std::vector<std::vector<double> > lattice_points = std::vector<std::vector<double> >(N,std::vector<double>(N));
	public:
		lattice(unsigned int s) : N(s) {}
		double point(int,int);
		void set(int,int,double);
};

*/

template <typename T> 
size_t lattice<T>::size() const {
	return N;
}

template <typename T>
T lattice<T>::point(int x, int y) {
	double val = this->lattice_points[mod(x, (int) N)][mod(y, (int) N)];
	return val;
};

template <typename T> 
void lattice<T>::set(int x, int y, T val) {
	this->lattice_points[mod(x, (int) N)][mod(y, (int) N)] = val;
};

template <typename T>  template <typename R> 
R lattice<T>::mod(R a, R b) {
	T ret = fmod(a, b);
	if(ret <0){
		ret+=b;
	};
	return ret;
};

template<typename T>
lattice<T>::lattice(const lattice& lat) : N(lat.size()) {
	this-> lattice_points = lat.lattice_points;
};

template <typename T>
lattice<T>& lattice<T>::operator=(const lattice& lat) {
	if( this-> size() != lat.size()) {
		throw std::invalid_argument("latices not the same size");	
	};
	this -> lattice_points = lat.lattice_points;
	return *this;
};

void angle_lattice::set(int x, int y, double ang) {
	int num = (*this).getN();
	lattice<double>::set(x, y, ang);
//	( this -> point(mod(x, num), mod(y, num) ) = mod(point(mod(x, num), mod(y, num)), 2*M_PI);
};
