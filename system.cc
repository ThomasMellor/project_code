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

int lattice::size() {
	return N;
}

double lattice::point(int x, int y) {
	return this->lattice_points[ mod(x, N)][ mod(y, N)];
};

void lattice::set(int x, int y, double ang) {
	this->lattice_points.at(mod(x, N)).at(mod(y, N)) = mod(ang, 2*M_PI);
};

void lattice::normalise(int x, int y) {
	this -> lattice_points.at(mod(x, N)).at(mod(y, N)) = mod(point(x, y), 2*M_PI);
};

template <typename T> T lattice::mod(T a, T b) {
	T ret = fmod(a, b);
	if(ret <0){
		ret+=b;
	};
	return ret;
};

