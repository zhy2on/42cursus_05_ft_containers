#include "../../containers/vector.hpp"
#include <iostream>

int main()
{
	ft::vector<int> v(5, 2);
	ft::vector<int>::iterator it;

	for (it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";

	std::cout << std::endl;

	ft::vector<int> v2(v.begin(), v.end());
	for (it = v2.begin(); it != v2.end(); it++)
		std::cout << *it << " ";
	
	std::cout << std::endl;

	ft::vector<int> v3(v2);
	for (it = v3.begin(); it != v3.end(); it++)
		std::cout << *it << " ";

	std::cout << std::endl;

	ft::vector<int> v4(7,7);

	v4 = v2;
	for (it = v4.begin(); it != v4.end(); it++)
		std::cout << *it << " ";	
	std::cout << std::endl;
	
	int k = 1;
	std::cout << "iterator pointer test" << std::endl;
	ft::vector_iterator<int>::pointer p = &k;
	std::cout << *p << std::endl;

	ft::reverse_iterator<ft::vector_iterator<int> > rit;
	std::cout << "rit" << std::endl;
	for (rit = v4.rbegin(); rit != v4.rend(); rit++)
		std::cout << *rit << " ";
}