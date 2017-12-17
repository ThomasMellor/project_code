#include "system.h"
#include "updater.h"
#include <math.h>
#include <random>

double sin_points(const angle_lattice&, int, int, int, int);
double cos_points(const angle_lattice&, int, int, int, int);

angle_lattice update_lattice(const angle_lattice& lat, parameters& par, double dt) {
	//std::random_device rd;
	//std::mt19937 gen(rd());
	//std::uniform_real_distribution<> dis(-0.5,0.5);
	angle_lattice new_lat(lat.size());


	if((lat.size() % 2) == 0) {
		new_lat = update_even(lat, par, dt);

	} else {
		new_lat = update_odd(new_lat, par, dt);
	};
	return new_lat;
};

double parameters::random_real() {
	return ((double) urd(rng)/rn_div) - 0.5;
};

double sin_points(const angle_lattice& lat, int i1, int j1, int i2, int j2) {
	return sin(lat.point(i1, j1) - lat.point(i2, j2));
};

double cos_points(const angle_lattice& lat, int i1, int j1, int i2, int j2) {
	return cos(lat.point(i1, j1) - lat.point(i2, j2));
};

angle_lattice update_even(const angle_lattice& lat, parameters& par, double dt) {
	//std::random_device rd;
	//std::mt19937 gen(rd());
	//std::uniform_real_distribution<> dis(-0.5,0.5);
	int N = lat.size();
	angle_lattice new_lat(lat.size());
	double sqrtdt = sqrt(dt);

	//bottom left

	int i = 0, j = 0;

	double ang_mid = lat.point(i, j);
	double ang_up = lat.point(i, j + 1);
	double ang_down = lat.point(i, N - 1);
	double ang_left = lat.point(N - 1, j);
	double ang_right = lat.point(i + 1, j);

	double sin_left = sin(ang_mid - ang_left);
	double sin_right = sin(ang_mid - ang_right);
	double sin_up = sin(ang_mid - ang_up);
	double sin_down = sin(ang_mid - ang_down);

	double cos_left = cos(ang_mid - ang_left);
	double cos_right = cos(ang_mid - ang_right);
	double cos_up = cos(ang_mid - ang_up);
	double cos_down = cos(ang_mid - ang_down);

	double mid_val = ang_mid +
		dt*(-par.Dx*(sin_right + sin_left)
			-par.Dy*(sin_up + sin_down)
			-par.Lx/2*(cos_left + cos_right - 2)
			-par.Ly/2*(cos_up + cos_down - 2));
			+sqrtdt*2*M_PI*par.Cl*par.random_real();
	new_lat.set(i, j, mid_val);

	double left_val = ang_left + new_lat.point(N - 1, j) +
		dt*(-par.Dx*(-sin_left) -par.Lx/2*cos_left + par.Lx + par.Ly);
			+sqrtdt*2*par.Cl*par.random_real();
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

        ang_mid = lat.point(i, j);
		ang_up = lat.point(i, j + 1);
		ang_down = lat.point(i, N - 1);
		ang_left = lat.point(i - 1, j);
		ang_right = lat.point(i + 1, j);

		sin_left = sin(ang_mid - ang_left);
		sin_right = sin(ang_mid - ang_right);
		sin_up = sin(ang_mid - ang_up);
		sin_down = sin(ang_mid - ang_down);

		cos_left = cos(ang_mid - ang_left);
		cos_right = cos(ang_mid - ang_right);
		cos_up = cos(ang_mid - ang_up);
		cos_down = cos(ang_mid - ang_down);

		mid_val = ang_mid +
			dt*(-par.Dx*(sin_right + sin_left)
				-par.Dy*(sin_up + sin_down)
				-par.Lx/2*(cos_left + cos_right - 2)
				-par.Ly/2*(cos_up + cos_down - 2));
				+sqrtdt*2*M_PI*par.Cl*par.random_real();
		new_lat.set(i, j, mid_val);

		left_val = ang_left + new_lat.point(i - 1, j) +
			dt*(-par.Dx*(-sin_left) -par.Lx/2*cos_left + par.Lx + par.Ly);
			   +sqrtdt*2*par.Cl*par.random_real();
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

			ang_mid = lat.point(i, j);
			ang_up = lat.point(i, j + 1);
			ang_down = lat.point(i, j - 1);
			ang_left = lat.point(i - 1, j);
			ang_right = lat.point(i + 1, j);

			sin_left = sin(ang_mid - ang_left);
			sin_right = sin(ang_mid - ang_right);
			sin_up = sin(ang_mid - ang_up);
			sin_down = sin(ang_mid - ang_down);

			cos_left = cos(ang_mid - ang_left);
			cos_right = cos(ang_mid - ang_right);
			cos_up = cos(ang_mid - ang_up);
			cos_down = cos(ang_mid - ang_down);

			mid_val = ang_mid +
				dt*(-par.Dx*(sin_right + sin_left)
				-par.Dy*(sin_up + sin_down)
				-par.Lx/2*(cos_left + cos_right - 2)
				-par.Ly/2*(cos_up + cos_down - 2));
			+sqrtdt*2*M_PI*par.Cl*par.random_real();
			new_lat.set(i, j, mid_val);

			left_val = ang_left + new_lat.point(i - 1, j) +
                +dt*(-par.Dx*(-sin_left) -par.Lx/2*cos_left + par.Lx + par.Ly);
			   	+sqrtdt*2*par.Cl*par.random_real();
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
		ang_mid = lat.point(i, j);
		ang_up = lat.point(i, j + 1);
		ang_down = lat.point(i, j - 1);
		ang_left = lat.point(N - 1, j);
		ang_right = lat.point(i + 1, j);

		sin_left = sin(ang_mid - ang_left);
		sin_right = sin(ang_mid - ang_right);
		sin_up = sin(ang_mid - ang_up);
		sin_down = sin(ang_mid - ang_down);

		cos_left = cos(ang_mid - ang_left);
		cos_right = cos(ang_mid - ang_right);
		cos_up = cos(ang_mid - ang_up);
		cos_down = cos(ang_mid - ang_down);

		mid_val = ang_mid +
			dt*(-par.Dx*(sin_right + sin_left)
				-par.Dy*(sin_up + sin_down)
				-par.Lx/2*(cos_left + cos_right - 2)
				-par.Ly/2*(cos_up + cos_down - 2));
				+sqrtdt*2*M_PI*par.Cl*par.random_real();
		new_lat.set(i, j, mid_val);

		left_val = ang_left + new_lat.point(N - 1, j) +
			dt*(-par.Dx*(-sin_left) -par.Lx/2*cos_left + par.Lx + par.Ly);
            +sqrtdt*2*par.Cl*par.random_real();
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
		ang_mid = lat.point(i, j);
		ang_up = lat.point(i, 0);
		ang_down = lat.point(i, j - 1);
		ang_left = lat.point(i - 1, j);
		ang_right = lat.point(i + 1, j);

		sin_left = sin(ang_mid - ang_left);
		sin_right = sin(ang_mid - ang_right);
		sin_up = sin(ang_mid - ang_up);
		sin_down = sin(ang_mid - ang_down);

		cos_left = cos(ang_mid - ang_left);
		cos_right = cos(ang_mid - ang_right);
		cos_up = cos(ang_mid - ang_up);
		cos_down = cos(ang_mid - ang_down);

		mid_val = ang_mid +
			dt*(-par.Dx*(sin_right + sin_left)
				-par.Dy*(sin_up + sin_down)
				-par.Lx/2*(cos_left + cos_right - 2)
				-par.Ly/2*(cos_up + cos_down - 2));
				+sqrtdt*2*M_PI*par.Cl*par.random_real();
		new_lat.set(i, j, mid_val);

		left_val = ang_left + new_lat.point(i - 1, j) +
			+dt*(-par.Dx*(-sin_left) -par.Lx/2*cos_left + par.Lx + par.Ly);
			   +sqrtdt*2*par.Cl*par.random_real();
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

	ang_mid = lat.point(i, j);
	ang_up = lat.point(i, 0);
	ang_down = lat.point(i, j - 1);
	ang_left = lat.point(i - 1, j);
	ang_right = lat.point(0, j);

	sin_left = sin(ang_mid - ang_left);
	sin_right = sin(ang_mid - ang_right);
	sin_up = sin(ang_mid - ang_up);
	sin_down = sin(ang_mid - ang_down);

	cos_left = cos(ang_mid - ang_left);
	cos_right = cos(ang_mid - ang_right);
	cos_up = cos(ang_mid - ang_up);
	cos_down = cos(ang_mid - ang_down);

	mid_val = ang_mid +
		dt*(-par.Dx*(sin_right + sin_left)
			-par.Dy*(sin_up + sin_down)
			-par.Lx/2*(cos_left + cos_right - 2)
			-par.Ly/2*(cos_up + cos_down - 2));
			+sqrtdt*2*M_PI*par.Cl*par.random_real();
	new_lat.set(i, j, mid_val);

	left_val = ang_left + new_lat.point(i - 1, j) +
		+dt*(-par.Dx*(-sin_left) -par.Lx/2*cos_left + par.Lx + par.Ly);
			+sqrtdt*2*par.Cl*par.random_real();
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

		ang_mid = lat.point(i, j);
		ang_up = lat.point(i, j + 1);
		ang_down = lat.point(i, j - 1);
		ang_left = lat.point(i - 1, j);
		ang_right = lat.point(0, j);

		sin_left = sin(ang_mid - ang_left);
		sin_right = sin(ang_mid - ang_right);
		sin_up = sin(ang_mid - ang_up);
		sin_down = sin(ang_mid - ang_down);

		cos_left = cos(ang_mid - ang_left);
		cos_right = cos(ang_mid - ang_right);
		cos_up = cos(ang_mid - ang_up);
		cos_down = cos(ang_mid - ang_down);

		mid_val = ang_mid +
			dt*(-par.Dx*(sin_right + sin_left)
				-par.Dy*(sin_up + sin_down)
				-par.Lx/2*(cos_left + cos_right - 2)
				-par.Ly/2*(cos_up + cos_down - 2))
				+sqrtdt*2*M_PI*par.Cl*par.random_real();
		new_lat.set(i, j, mid_val);

		left_val = ang_left + new_lat.point(i - 1, j) +
			+dt*(-par.Dx*(-sin_left) -par.Lx/2*cos_left + par.Lx + par.Ly);
			   +sqrtdt*2*par.Cl*par.random_real();
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

angle_lattice update_odd(const angle_lattice& lat, parameters& par, double dt) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-0.5,0.5);
	double sqrtdt = sqrt(dt);
	angle_lattice new_lat(lat.size());
	int N = lat.size();

	//bottom left

	int i = 0, j = 0;

	double ang_mid = lat.point(i, j);
    double ang_up = lat.point(i, j + 1);
    double ang_down = lat.point(i, N - 1);
    double ang_left = lat.point(N - 1, j);
    double ang_right = lat.point(i + 1, j);

    double sin_left = sin(ang_mid - ang_left);
    double sin_right = sin(ang_mid - ang_right);
    double sin_up = sin(ang_mid - ang_up);
    double sin_down = sin(ang_mid - ang_down);

    double cos_left = cos(ang_mid - ang_left);
    double cos_right = cos(ang_mid - ang_right);
    double cos_up = cos(ang_mid - ang_up);
    double cos_down = cos(ang_mid - ang_down);

    double mid_val = ang_mid +
        dt*(-par.Dx*(sin_right + sin_left)
            -par.Dy*(sin_up + sin_down)
            -par.Lx/2*(cos_left + cos_right - 2)
            -par.Ly/2*(cos_up + cos_down - 2))
        +sqrtdt*2*M_PI*par.Cl*par.random_real();
    new_lat.set(i, j, mid_val);

    // bottom

    j = 0;

    for(int i = 0; i < N - 1; ++i){
        ang_mid = lat.point(i, j);
        ang_up = lat.point(i, j + 1);
        ang_down = lat.point(i, N - 1);
        ang_left = lat.point(i - 1, j);
        ang_right = lat.point(i + 1, j);

        sin_left = sin(ang_mid - ang_left);
        sin_right = sin(ang_mid - ang_right);
        sin_up = sin(ang_mid - ang_up);
        sin_down = sin(ang_mid - ang_down);

        cos_left = cos(ang_mid - ang_left);
        cos_right = cos(ang_mid - ang_right);
        cos_up = cos(ang_mid - ang_up);
        cos_down = cos(ang_mid - ang_down);

        mid_val = ang_mid +
            dt*(-par.Dx*(sin_right + sin_left)
            -par.Dy*(sin_up + sin_down)
            -par.Lx/2*(cos_left + cos_right - 2)
            -par.Ly/2*(cos_up + cos_down - 2))
            +sqrtdt*2*M_PI*par.Cl*par.random_real();
        new_lat.set(i, j, mid_val);
    };

	//middle
	for(int i = 1; i < N - 1; ++i) {
		for(int j = 1; j < N - 1; ++j) {

			ang_mid = lat.point(i, j);
			ang_up = lat.point(i, j + 1);
			ang_down = lat.point(i, j - 1);
			ang_left = lat.point(i - 1, j);
			ang_right = lat.point(i + 1, j);

			sin_left = sin(ang_mid - ang_left);
			sin_right = sin(ang_mid - ang_right);
			sin_up = sin(ang_mid - ang_up);
			sin_down = sin(ang_mid - ang_down);

			cos_left = cos(ang_mid - ang_left);
			cos_right = cos(ang_mid - ang_right);
			cos_up = cos(ang_mid - ang_up);
			cos_down = cos(ang_mid - ang_down);

			mid_val = ang_mid +
				dt*(-par.Dx*(sin_right + sin_left)
				-par.Dy*(sin_up + sin_down)
				-par.Lx/2*(cos_left + cos_right - 2)
				-par.Ly/2*(cos_up + cos_down - 2))
                +sqrtdt*2*M_PI*par.Cl*par.random_real();
			new_lat.set(i, j, mid_val);
		};
	};

    //left up

    i = 0;

    for(int j = 1; j < N - 1; ++j){
        ang_mid = lat.point(i, j);
        ang_up = lat.point(i, j + 1);
        ang_down = lat.point(i, j - 1);
        ang_left = lat.point(N - 1, j);
        ang_right = lat.point(i + 1, j);

        sin_left = sin(ang_mid - ang_left);
        sin_right = sin(ang_mid - ang_right);
        sin_up = sin(ang_mid - ang_up);
        sin_down = sin(ang_mid - ang_down);

        cos_left = cos(ang_mid - ang_left);
        cos_right = cos(ang_mid - ang_right);
        cos_up = cos(ang_mid - ang_up);
        cos_down = cos(ang_mid - ang_down);

        mid_val = ang_mid +
            dt*(-par.Dx*(sin_right + sin_left)
            -par.Dy*(sin_up + sin_down)
            -par.Lx/2*(cos_left + cos_right - 2)
            -par.Ly/2*(cos_up + cos_down - 2))
            +sqrtdt*2*M_PI*par.Cl*par.random_real();
        new_lat.set(i, j, mid_val);
    };

    //top left

    i = 0, j = N - 1;

        ang_mid = lat.point(i, j);
        ang_up = lat.point(i, 0);
        ang_down = lat.point(i, j - 1);
        ang_left = lat.point(N - 1, j);
        ang_right = lat.point(i + 1, j);

        sin_left = sin(ang_mid - ang_left);
        sin_right = sin(ang_mid - ang_right);
        sin_up = sin(ang_mid - ang_up);
        sin_down = sin(ang_mid - ang_down);

        cos_left = cos(ang_mid - ang_left);
        cos_right = cos(ang_mid - ang_right);
        cos_up = cos(ang_mid - ang_up);
        cos_down = cos(ang_mid - ang_down);

        mid_val = ang_mid +
        dt*(-par.Dx*(sin_right + sin_left)
            -par.Dy*(sin_up + sin_down)
            -par.Lx/2*(cos_left + cos_right - 2)
            -par.Ly/2*(cos_up + cos_down - 2))
            +sqrtdt*2*M_PI*par.Cl*par.random_real();
        new_lat.set(i, j, mid_val);

	//top

    j = N - 1;

    for(int i = 1; i < N - 1; ++i){
        ang_mid = lat.point(i, j);
        ang_up = lat.point(i, 0);
        ang_down = lat.point(i, j - 1);
        ang_left = lat.point(i - 1, j);
        ang_right = lat.point(i + 1, j);

        sin_left = sin(ang_mid - ang_left);
        sin_right = sin(ang_mid - ang_right);
        sin_up = sin(ang_mid - ang_up);
        sin_down = sin(ang_mid - ang_down);

        cos_left = cos(ang_mid - ang_left);
        cos_right = cos(ang_mid - ang_right);
        cos_up = cos(ang_mid - ang_up);
        cos_down = cos(ang_mid - ang_down);

        mid_val = ang_mid +
            dt*(-par.Dx*(sin_right + sin_left)
            -par.Dy*(sin_up + sin_down)
            -par.Lx/2*(cos_left + cos_right - 2)
            -par.Ly/2*(cos_up + cos_down - 2))
            +sqrtdt*2*M_PI*par.Cl*par.random_real();
        new_lat.set(i, j, mid_val);
    };

    // top right

    i = N - 1, j = N - 1;

    ang_mid = lat.point(i, j);
    ang_up = lat.point(i, 0);
    ang_down = lat.point(i, j - 1);
    ang_left = lat.point(i - 1, j);
    ang_right = lat.point(0, j);

    sin_left = sin(ang_mid - ang_left);
    sin_right = sin(ang_mid - ang_right);
    sin_up = sin(ang_mid - ang_up);
    sin_down = sin(ang_mid - ang_down);

    cos_left = cos(ang_mid - ang_left);
    cos_right = cos(ang_mid - ang_right);
    cos_up = cos(ang_mid - ang_up);
    cos_down = cos(ang_mid - ang_down);

    mid_val = ang_mid +
    dt*(-par.Dx*(sin_right + sin_left)
        -par.Dy*(sin_up + sin_down)
        -par.Lx/2*(cos_left + cos_right - 2)
        -par.Ly/2*(cos_up + cos_down - 2))
        +sqrtdt*2*M_PI*par.Cl*par.random_real();
    new_lat.set(i, j, mid_val);

    //right up

    i = N - 1;

    for(int j = 1; j < N - 1; ++j){
        ang_mid = lat.point(i, j);
        ang_up = lat.point(i, j + 1);
        ang_down = lat.point(i, j - 1);
        ang_left = lat.point(i - 1, j);
        ang_right = lat.point(0, j);

        sin_left = sin(ang_mid - ang_left);
        sin_right = sin(ang_mid - ang_right);
        sin_up = sin(ang_mid - ang_up);
        sin_down = sin(ang_mid - ang_down);

        cos_left = cos(ang_mid - ang_left);
        cos_right = cos(ang_mid - ang_right);
        cos_up = cos(ang_mid - ang_up);
        cos_down = cos(ang_mid - ang_down);

        mid_val = ang_mid +
            dt*(-par.Dx*(sin_right + sin_left)
            -par.Dy*(sin_up + sin_down)
            -par.Lx/2*(cos_left + cos_right - 2)
            -par.Ly/2*(cos_up + cos_down - 2))
            +sqrtdt*2*M_PI*par.Cl*par.random_real();
        new_lat.set(i, j, mid_val);

    };

    //bottom right

    i = N - 1, j = 0;

    ang_mid = lat.point(i, j);
    ang_up = lat.point(i, j + 1);
    ang_down = lat.point(i, N - 1);
    ang_left = lat.point(i - 1, j);
    ang_right = lat.point(0, j);

    sin_left = sin(ang_mid - ang_left);
    sin_right = sin(ang_mid - ang_right);
    sin_up = sin(ang_mid - ang_up);
    sin_down = sin(ang_mid - ang_down);

    cos_left = cos(ang_mid - ang_left);
    cos_right = cos(ang_mid - ang_right);
    cos_up = cos(ang_mid - ang_up);
    cos_down = cos(ang_mid - ang_down);

    mid_val = ang_mid +
    dt*(-par.Dx*(sin_right + sin_left)
        -par.Dy*(sin_up + sin_down)
        -par.Lx/2*(cos_left + cos_right - 2)
        -par.Ly/2*(cos_up + cos_down - 2))
        +sqrtdt*2*M_PI*par.Cl*par.random_real();
    new_lat.set(i, j, mid_val);

	return new_lat;
};




