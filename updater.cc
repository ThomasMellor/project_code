#include "system.h"
#include "updater.h"
#include <math.h>
#include <random>

double sin_points(const angle_lattice&, int, int, int, int);
double cos_points(const angle_lattice&, int, int, int, int);

angle_lattice update_lattice(const angle_lattice& lat, const parameters& par, double dt) {	
	std::random_device rd; 
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-0.5,0.5);
	angle_lattice new_lat(lat.size());


	if((lat.size() % 2) == 0) {
		new_lat = update_odd(lat, par, dt);                       	
		
	} else {
		new_lat = update_odd(new_lat, par, dt);	
	};	
	return new_lat;
};

double sin_points(const angle_lattice& lat, int i1, int j1, int i2, int j2) {
	return sin(lat.point(i1, j1) - lat.point(i2, j2));
};

double cos_points(const angle_lattice& lat, int i1, int j1, int i2, int j2) {
	return cos(lat.point(i1, j1) - lat.point(i2, j2));
};

angle_lattice update_even(const angle_lattice& lat, const parameters& par, double dt) {
	std::random_device rd;                                                                                    
	std::mt19937 gen(rd());                                                                                   
	std::uniform_real_distribution<> dis(-0.5,0.5);                                                           
	int N = lat.size();
	angle_lattice new_lat(lat.size());	
	double sqrtdt = sqrt(dt);

	//bottom left 

	int i = 0, j = 0;	

	double sin_left = sin_points(lat, i, j, N - 1, j);
	double sin_right = sin_points(lat, i, j, i + 1, j);
	double sin_up = sin_points(lat, i, j, i, j + 1);
	double sin_down = sin_points(lat, i, j, i, N - 1);

	double cos_left = cos_points(lat, i, j, N - 1, j);                                                
	double cos_right = cos_points(lat, i, j, i + 1, j);                                               
	double cos_up = cos_points(lat, i, j, i, j + 1);                                                  
	double cos_down = cos_points(lat, i, j, i, N - 1);
			
	double mid_val = lat.point(i, j) + 
		dt*(-par.Dx*(sin_right + sin_left) 
			-par.Dy*(sin_up + sin_down)
			-par.Lx/2*(cos_left + cos_right - 2)
			-par.Ly/2*(cos_up + cos_down - 2))
			+sqrtdt*2*M_PI*par.Cl*dis(gen);
	new_lat.set(i, j, mid_val);
			
	double left_val = lat.point(N - 1, j) + new_lat.point(N - 1, j) +
		dt*(-par.Dx*(-sin_left) -par.Lx/2*cos_left + par.Lx + par.Ly)
			+sqrtdt*2*par.Cl*dis(gen);
	new_lat.set(N - 1, j, left_val);
			
	double right_val = new_lat.point(i + 1, j) +
		dt*(-par.Dx*(-sin_right) - par.Lx/2*cos_right);
	new_lat.set(i + 1, j, right_val);
			
	double up_val = new_lat.point(i, j + 1) +
		dt*(-par.Dy*(-sin_up) -par.Ly/2*cos_up);
	new_lat.set(i, j + 1, up_val);
		
	double down_val = new_lat.point(i, N - 1) +
		dt*(-par.Dy*(-sin_down) - par.Ly/2*cos_down);
	new_lat.set(i, N - 1, down_val);

	//bottom
	
	j = 0;
	
	for(i = 2; i < N-1; i+=2) {
		sin_left = sin_points(lat, i, j, i - 1, j);
		sin_right = sin_points(lat, i, j, i + 1, j);
		sin_up = sin_points(lat, i, j, i, j + 1);
		sin_down = sin_points(lat, i, j, i, N - 1);

		cos_left = cos_points(lat, i, j, i - 1, j);                                                
	        cos_right = cos_points(lat, i, j, i + 1, j);                                               
	        cos_up = cos_points(lat, i, j, i, j + 1);                                                  
	        cos_down = cos_points(lat, i, j, i, N - 1);
			
		mid_val = lat.point(i, j) + 
			dt*(-par.Dx*(sin_right + sin_left) 
				-par.Dy*(sin_up + sin_down)
				-par.Lx/2*(cos_left + cos_right - 2)
				-par.Ly/2*(cos_up + cos_down - 2))
				+sqrtdt*2*M_PI*par.Cl*dis(gen);
		new_lat.set(i, j, mid_val);
			
		left_val = lat.point(i - 1, j) + new_lat.point(i - 1, j) +
			dt*(-par.Dx*(-sin_left) -par.Lx/2*cos_left + par.Lx + par.Ly)
			   +sqrtdt*2*par.Cl*dis(gen);
		new_lat.set(i - 1, j, left_val);
			
		right_val = new_lat.point(i + 1, j) +
			dt*(-par.Dx*(-sin_right) - par.Lx/2*cos_right);
		new_lat.set(i + 1, j, right_val);
			
		up_val = new_lat.point(i, j + 1) +
			dt*(-par.Dy*(-sin_up) -par.Ly/2*cos_up);
		new_lat.set(i, j + 1, up_val);
		
		down_val = new_lat.point(i, N - 1) +
			dt*(-par.Dy*(-sin_down) - par.Ly/2*cos_down);
		new_lat.set(i, N - 1, down_val);
		};

	//middle	

	for(j = 1; j < N-1; j++) {
		i = 2;
		if ( (j % 2) != 0) {
			i = 1;
		};
		for(i; i < N-1; i+=2) {
			sin_left = sin_points(lat, i, j, i - 1, j);
			sin_right = sin_points(lat, i, j, i + 1, j);
			sin_up = sin_points(lat, i, j, i, j + 1);
			sin_down = sin_points(lat, i, j, i, j - 1);

			cos_left = cos_points(lat, i, j, i - 1, j);                                                
	        	cos_right = cos_points(lat, i, j, i + 1, j);                                               
	        	cos_up = cos_points(lat, i, j, i, j + 1);                                                  
	        	cos_down = cos_points(lat, i, j, i, j - 1);
			
			mid_val = lat.point(i, j) + 
				dt*(-par.Dx*(sin_right + sin_left) 
				-par.Dy*(sin_up + sin_down)
				-par.Lx/2*(cos_left + cos_right - 2)
				-par.Ly/2*(cos_up + cos_down - 2))
			+sqrtdt*2*M_PI*par.Cl*dis(gen);
			new_lat.set(i, j, mid_val);
			
			left_val = lat.point(i - 1, j) + new_lat.point(i - 1, j) +
				dt*(-par.Dx*(-sin_left) -par.Lx/2*cos_left + par.Lx + par.Ly)
			   	+sqrtdt*2*par.Cl*dis(gen);
			new_lat.set(i - 1, j, left_val);
			
			right_val = new_lat.point(i + 1, j) +
				dt*(-par.Dx*(-sin_right) - par.Lx/2*cos_right);
			new_lat.set(i + 1, j, right_val);
			
			up_val = new_lat.point(i, j + 1) +
				dt*(-par.Dy*(-sin_up) -par.Ly/2*cos_up);
			new_lat.set(i, j + 1, up_val);
		
			down_val = new_lat.point(i, j - 1) +
				dt*(-par.Dy*(-sin_down) - par.Ly/2*cos_down);
			new_lat.set(i, j - 1, down_val);
		};
	};

	//left up
	
	i = 0;
	
	for(j = 2; j < N-1; j+=2) {
		sin_left = sin_points(lat, i, j, N - 1, j);
		sin_right = sin_points(lat, i, j, i + 1, j);
		sin_up = sin_points(lat, i, j, i, j + 1);
		sin_down = sin_points(lat, i, j, i, j - 1);

		cos_left = cos_points(lat, i, j, N - 1, j);                                                
	        cos_right = cos_points(lat, i, j, i + 1, j);                                               
	        cos_up = cos_points(lat, i, j, i, j + 1);                                                  
	        cos_down = cos_points(lat, i, j, i, j - 1);
			
		mid_val = lat.point(i, j) + 
			dt*(-par.Dx*(sin_right + sin_left) 
				-par.Dy*(sin_up + sin_down)
				-par.Lx/2*(cos_left + cos_right - 2)
				-par.Ly/2*(cos_up + cos_down - 2))
				+sqrtdt*2*M_PI*par.Cl*dis(gen);
		new_lat.set(i, j, mid_val);
			
		left_val = lat.point(N - 1, j) + new_lat.point(N - 1, j) +
			dt*(-par.Dx*(-sin_left) -par.Lx/2*cos_left + par.Lx + par.Ly)
			   +sqrtdt*2*par.Cl*dis(gen);
		new_lat.set(N - 1, j, left_val);
			
		right_val = new_lat.point(i + 1, j) +
			dt*(-par.Dx*(-sin_right) - par.Lx/2*cos_right);
		new_lat.set(i + 1, j, right_val);
			
		up_val = new_lat.point(i, j + 1) +
			dt*(-par.Dy*(-sin_up) -par.Ly/2*cos_up);
		new_lat.set(i, j + 1, up_val);
		
		down_val = new_lat.point(i, j - 1) +
			dt*(-par.Dy*(-sin_down) - par.Ly/2*cos_down);
		new_lat.set(i, j - 1, down_val);
	};

	//top

	j = N - 1;	

	for(i = 1; i < N-1; i+=2) {
		sin_left = sin_points(lat, i, j, i - 1, j);
		sin_right = sin_points(lat, i, j, i + 1, j);
		sin_up = sin_points(lat, i, j, i, 0);
		sin_down = sin_points(lat, i, j, i, j - 1);

		cos_left = cos_points(lat, i, j, i - 1, j);                                                
	        cos_right = cos_points(lat, i, j, i + 1, j);                                               
	        cos_up = cos_points(lat, i, j, i, 0);                                                  
	        cos_down = cos_points(lat, i, j, i, j - 1);
			
		mid_val = lat.point(i, j) + 
			dt*(-par.Dx*(sin_right + sin_left) 
				-par.Dy*(sin_up + sin_down)
				-par.Lx/2*(cos_left + cos_right - 2)
				-par.Ly/2*(cos_up + cos_down - 2))
				+sqrtdt*2*M_PI*par.Cl*dis(gen);
		new_lat.set(i, j, mid_val);
			
		left_val = lat.point(i - 1, j) + new_lat.point(i - 1, j) +
			dt*(-par.Dx*(-sin_left) -par.Lx/2*cos_left + par.Lx + par.Ly)
			   +sqrtdt*2*par.Cl*dis(gen);
		new_lat.set(i - 1, j, left_val);
			
		right_val = new_lat.point(i + 1, j) +
			dt*(-par.Dx*(-sin_right) - par.Lx/2*cos_right);
		new_lat.set(i + 1, j, right_val);
			
		up_val = new_lat.point(i, 0) +
			dt*(-par.Dy*(-sin_up) -par.Ly/2*cos_up);
		new_lat.set(i, 0, up_val);
		
		down_val = new_lat.point(i, j - 1) +
			dt*(-par.Dy*(-sin_down) - par.Ly/2*cos_down);
		new_lat.set(i, j - 1, down_val);
	};

	//top right 

	i = N - 1; j = N - 1;	

	sin_left = sin_points(lat, i, j, i - 1, j);
	sin_right = sin_points(lat, i, j, 0, j);
	sin_up = sin_points(lat, i, j, i, 0);
	sin_down = sin_points(lat, i, j, i, j - 1);

	cos_left = cos_points(lat, i, j, j - 1, j);                                                
	cos_right = cos_points(lat, i, j, 0, j);                                               
	cos_up = cos_points(lat, i, j, i, 0);                                                  
	cos_down = cos_points(lat, i, j, i, j - 1);
			
	mid_val = lat.point(i, j) + 
		dt*(-par.Dx*(sin_right + sin_left) 
			-par.Dy*(sin_up + sin_down)
			-par.Lx/2*(cos_left + cos_right - 2)
			-par.Ly/2*(cos_up + cos_down - 2))
			+sqrtdt*2*M_PI*par.Cl*dis(gen);
	new_lat.set(i, j, mid_val);
			
	left_val = lat.point(i - 1, j) + new_lat.point(i - 1, j) +
		dt*(-par.Dx*(-sin_left) -par.Lx/2*cos_left + par.Lx + par.Ly)
			+sqrtdt*2*par.Cl*dis(gen);
	new_lat.set(i - 1, j, left_val);
			
	right_val = new_lat.point(0, j) +
		dt*(-par.Dx*(-sin_right) - par.Lx/2*cos_right);
	new_lat.set(0, j, right_val);
			
	up_val = new_lat.point(i, 0) +
		dt*(-par.Dy*(-sin_up) -par.Ly/2*cos_up);
	new_lat.set(i, 0, up_val);
		
	down_val = new_lat.point(i, j - 1) +
		dt*(-par.Dy*(-sin_down) - par.Ly/2*cos_down);
	new_lat.set(i, j - 1, down_val);

	//right up

	i = N - 1;	

	for(j = 1; j < N-1; j+=2) {
		sin_left = sin_points(lat, i, j, i - 1, j);
		sin_right = sin_points(lat, i, j, 0, j);
		sin_up = sin_points(lat, i, j, i, j);
		sin_down = sin_points(lat, i, j, i, j - 1);

		cos_left = cos_points(lat, i, j, i - 1, j);                                                
	        cos_right = cos_points(lat, i, j, 0, j);                                               
	        cos_up = cos_points(lat, i, j, i, j);                                                  
	        cos_down = cos_points(lat, i, j, i, j - 1);
			
		mid_val = lat.point(i, j) + 
			dt*(-par.Dx*(sin_right + sin_left) 
				-par.Dy*(sin_up + sin_down)
				-par.Lx/2*(cos_left + cos_right - 2)
				-par.Ly/2*(cos_up + cos_down - 2))
				+sqrtdt*2*M_PI*par.Cl*dis(gen);
		new_lat.set(i, j, mid_val);
			
		left_val = lat.point(i - 1, j) + new_lat.point(i - 1, j) +
			dt*(-par.Dx*(-sin_left) -par.Lx/2*cos_left + par.Lx + par.Ly)
			   +sqrtdt*2*par.Cl*dis(gen);
		new_lat.set(i - 1, j, left_val);
			
		right_val = new_lat.point(0, j) +
			dt*(-par.Dx*(-sin_right) - par.Lx/2*cos_right);
		new_lat.set(0, j, right_val);
			
		up_val = new_lat.point(i, j + 1) +
			dt*(-par.Dy*(-sin_up) -par.Ly/2*cos_up);
		new_lat.set(i, j + 1, up_val);
		
		down_val = new_lat.point(i, j - 1) +
			dt*(-par.Dy*(-sin_down) - par.Ly/2*cos_down);
		new_lat.set(i, j - 1, down_val);
	};

	return new_lat;	
};

angle_lattice update_odd(const angle_lattice& lat, const parameters& par, double dt) {
	std::random_device rd;                                                                                    
	std::mt19937 gen(rd());                                                                                   
	std::uniform_real_distribution<> dis(-0.5,0.5);      
	angle_lattice new_lat(lat.size());
	int N = lat.size();
	double sqrtdt = sqrt(dt);
	for(int i = 0; i < N; ++i) {                                                                                
		for(int j=0; j < N; ++j) {                                                                            
			double val = lat.point(i,j)+                                                                      
				dt*(-par.Dx*( sin_points(lat, i, j, i+1, j) + sin_points(lat, i, j, i-1, j) )           
					-par.Dy*( sin_points(lat, i, j, i, j+1) + sin_points(lat, i, j, i, j-1) )            
					-par.Lx/2*( cos_points(lat, i, j, i+1, j) + cos_points(lat, i, j, i-1, j) -2)        
					-par.Ly/2*( cos_points(lat, i, j, i, j+1) + cos_points(lat, i, j, i, j-1) -2))          
				+sqrtdt*2*M_PI*par.Cl*dis(gen);                                                      
			new_lat.set(i,j,val);                                                                             
		};                                                                                                    
	};
	return new_lat;
};	




