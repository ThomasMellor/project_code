#include <vector>
#include <iostream>

int mod(int,int);

class lattice{
	private:
		const unsigned int N;
		std::vector<std::vector<double> > lattice_points = std::vector<std::vector<double> >(N,std::vector<double>(N));
	public:
		lattice(unsigned int s) : N(s) {}
		double point(int,int);
		void set(int,int,double);
};


double lattice::point(int x, int y) {
	return this->lattice_points[ mod(x, N)][ mod(y, N)];
};

void lattice::set(int x, int y, double ang) {
	this->lattice_points.at(mod(x, N)).at(mod(y, N)) = ang;
};

int mod(int a, int b) {
	int ret = a % b;
	if(ret <0){
		ret+=b;
	};
	return ret;
};



int main() {
	lattice sys(10);
	v
};
