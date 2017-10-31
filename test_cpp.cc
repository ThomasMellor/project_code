#include <iostream>
#include <vector>

class new_vec  {
	public:
		std::vector<int> vec;
		new_vec(std::vector<int> v) : vec(v) {};
		int change_element() const;
};


int new_vec::change_element() const {
	int b = (*this).vec[0];
	return b;
};


int main() {
	std::vector<int> v ={1,1};
	new_vec vec(v);
	vec.change_element();
}
