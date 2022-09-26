#include "../../containers/map.hpp"
#include <iostream>

int main()
{
	ft::map<char, int> m;

	m.insert(ft::make_pair('a', 1));
	m.insert(ft::make_pair('b', 1));
	m.insert(ft::make_pair('c', 1));

	std::cout << m.begin()->first << std::endl;
	m.erase(m.begin());
	std::cout << m.begin()->first << std::endl;
	m.erase(m.begin());
	std::cout << m.begin()->first << std::endl;
	m.erase(m.begin());
	std::cout << m.begin()->first << std::endl;
	m.erase(m.begin());
	return (0);
}
