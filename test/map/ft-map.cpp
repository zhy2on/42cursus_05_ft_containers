#include "../../containers/map.hpp"
#include <iostream>

int main()
{
	ft::map<char, int> m;

	m.insert(ft::make_pair('a', 1));

	std::cout << m.find('a')->first << std::endl;
	m.erase(m.begin());
	std::cout << m.find('a')->first << std::endl;
	return (0);
}
