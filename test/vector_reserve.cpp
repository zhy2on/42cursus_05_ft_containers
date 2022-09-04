#include "../containers/vector.hpp"
#include <iostream>

int main()
{
	ft::vector<int> v(5, 2);

	std::cout << v.capacity() << std::endl;

	v.reserve(100);
	for (int i = 0; i < v.size(); i++)
		std::cout << v[i] << std::endl;

	std::cout << v.capacity() << std::endl;
}