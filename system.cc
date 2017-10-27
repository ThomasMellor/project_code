#include <vector>
#include <iostream>
#include <math.h>
#include "system.h"

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

int lattice::size() const {
	return N;
}

double lattice::point(int x, int y) {
	double val = this->lattice_points[mod(x, N)][mod(y, N)];
	return val;
};

void lattice::set(int x, int y, double ang) {
	this->lattice_points[mod(x, N)][mod(y, N)] = mod(ang, 2*M_PI);
};

template <typename T> T lattice::mod(T a, T b) {
	T ret = fmod(a, b);
	if(ret <0){
		ret+=b;
	};
	return ret;
};

lattice::lattice(const lattice& lat) : N(lat.size()) {
	this-> lattice_points = lat.lattice_points;
};

lattice& lattice::operator=(const lattice& lat) {
	this -> lattice_points = lat.lattice_points;
	return *this;
};
