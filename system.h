#ifndef LATTICE_H
#define LATTICE_H

#include <vector>
#include <iostream>
#include <math.h>

/* Header code for the lattice templates and
 * implementations
 */



/*
 * Basic lattice template
 */
template<typename T> class lattice{
	private:
		const unsigned int N; //size
		std::vector<T> lattice_points = std::vector<T>(pow(N, 2)); //array of points
		static int point_1D(int, int, int);
		static int mv_inside(int, int); 
	protected:
		static double mod(double, double) ;
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
int lattice<T>::point_1D(int i, int j, int N) {
	return N*mv_inside(i, N) + mv_inside(j, N);
};

template <typename T>
int lattice<T>::mv_inside(int i, int j) {
	if( i >= 0 && i < j) { 
		return i;
	} else if(i == j) {
		return 0;
	} else {	
		return j-1;
	};
};

template <typename T>
T lattice<T>::point(int x, int y) const {
	return (*this).lattice_points[point_1D(x, y, N)]; //mod for periodic boundaries
};

template <typename T>
void lattice<T>::set(int x, int y, T val) {
	this->lattice_points[point_1D(x, y, N)] = val; //mod for periodic boundaries
};

/*
 * Constructors for lattice templates
 */

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

/*
 * Prints lattice to standard output
 */
template <typename T>
void print(lattice<T> const &lat) {
	for(int i = 0; i < lat.size(); i++) {
		for(int j = 0; j < lat.size(); j++) {
			std::cout << lat.point(i, j) << " ";
		};
		std::cout << std::endl;
	};
};

/*
 *returns the positive a mod b        
 */
template <typename T>
double lattice<T>::mod(double a, double b) {    
	double ret = fmod(a, b);    
		if(ret < 0){    
			ret += b;    
		};    
	return ret;    
};

/*
 * Lattice of angles
 */
class angle_lattice : public lattice<double> {
	public:
		virtual void set(int, int, double); // overloaded to be mod 2pi;
		angle_lattice(int N);
};

/*
 * Vortex lattice class which includes vortex number member
 * variables
 */
class vortex_lattice : public lattice<int> {
	private:
		int n_vor = 0;
		int n_anti_vor = 0;
	public:
		virtual void set(int, int, int); //overloaded so each point is an integer;
		vortex_lattice(int N);
		int num_vor() const {return n_vor;};
		int num_anti_vor() const {return n_anti_vor;}
		/*
		 * Sets the vortex lattice from the angle lattice lat
		 */
        vortex_lattice& set_vortex_lattice(angle_lattice const& lat);
};

template <typename T> int sign(T val) {
	if(val > 0) {return 1;};
	if(val < 0) {return -1;};
	return 0;
};

#endif

