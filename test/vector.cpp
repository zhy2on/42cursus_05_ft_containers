#include "../containers/vector.hpp"
#include <iostream>

int main()
{
	ft::vector<int> v(5,3);
	ft::vector<int>::iterator it;

	for (it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";

	std::cout << std::endl;

	ft::vector<int> v2(v.begin(), v.end());
	for (it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";	
}