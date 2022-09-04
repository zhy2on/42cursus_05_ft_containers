#include "../../containers/vector.hpp"
#include <iostream>

int main()
{
	ft::vector<int> v(5, 2);
	ft::vector<int>::iterator it;
	ft::vector<int>::reverse_iterator rit;

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

	std::cout << std::endl << "rbegin" << std::endl;
	for (rit = v.rbegin(); rit != v.rend(); rit++)
		std::cout << *rit << " ";
	std::cout << std::endl;
	for (rit = v2.rbegin(); rit != v2.rend(); rit++)
		std::cout << *rit << " ";
}