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
	protected:
		template <typename R, typename S>  static T mod(R, S) ;    
	public:    
		lattice(unsigned int);    	
		lattice(const lattice&);
		lattice& operator=(const lattice&);
		~lattice() {};

		T point(int, int) const;    
		void set(int, int, T);    
		unsigned int size() const;
};    

template <typename T>    
unsigned int lattice<T>::size() const {    
	return N;    
}    
    
template <typename T>    
T lattice<T>::point(int x, int y) const {    
	T val = (*this).lattice_points[mod(x, N)][mod(y, N)];    
	return val; 
};    
    
template <typename T>    
void lattice<T>::set(int x, int y, T val) {    
	this->lattice_points[mod(x, N)][mod(y, N)] = val;    
};    
    
template <typename T> template <typename R, typename S>    
T lattice<T>::mod(R a, S b) {    
	T ret = fmod(a, b);    
	if(ret < 0){    
		ret += b;    
	};    
	return ret;    
};    
    
template<typename T>        
lattice<T>::lattice(unsigned int s) : N(s) {};    
    
template<typename T>    
lattice<T>::lattice(const lattice& lat) : N(lat.size()) {    
	    this-> lattice_points = lat.lattice_points;    
};    
    
template <typename T>    
lattice<T>& lattice<T>::operator=(const lattice& lat) {    
	if( this -> size() != lat.size()) {    
		throw std::invalid_argument("latices not the same size");    
	};    
this -> lattice_points = lat.lattice_points;    
return *this;    
};

template <typename T> 
void print(lattice<T> const &lat) {
	for(int i = 0; i < lat.size(); i++) {
		for(int j = 0; j < lat.size(); j++) {
			std::cout << lat.point(i, j) << " ";
		};
		std::cout << std::endl;
	};	
};

class angle_lattice : public lattice<double> {
	public:
		virtual void set(int, int, double);
		angle_lattice(int N);
};

class vortex_lattice : public lattice<int> {
	private:
		int n_vor = 0;
		int n_anti_vor = 0;
	public:
		virtual void set(int, int, int);
		vortex_lattice(int N);
		int num_vor() const {return n_vor;};
		int num_anti_vor() const {return n_anti_vor;}
};

template <typename T> int sign(T val) {
	if(val > 0) {return 1;};                                                                                  
	if(val < 0) {return -1;};                                                                                 
	return 0;    
};

#endif

