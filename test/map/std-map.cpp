#include <iostream>
#include <map>

int main()
{
	std::map<char, int> m;
	std::map<int, int> m2;

	m.insert(std::make_pair('a', 1));
	m.insert(std::make_pair('b', 1));
	m.insert(std::make_pair('c', 1));

	std::cout << m.begin()->first << std::endl;
	m.erase(m.begin());
	std::cout << m.begin()->first << std::endl;
	m.erase(m.begin());
	std::cout << m.begin()->first << std::endl;
	m.erase(m.begin());
	std::cout << m.begin()->first << std::endl;
	m.erase(m.begin());

	// m2.insert(std::make_pair(1, 1));
	// m2.insert(std::make_pair(2, 1));
	// m2.insert(std::make_pair(3, 1));

	// std::cout << m2.begin()->first << std::endl;
	// m2.erase(m2.begin());
	// std::cout << m2.begin()->first << std::endl;
	// m2.erase(m2.begin());
	// std::cout << m2.begin()->first << std::endl;
	// m2.erase(m2.begin());
	// std::cout << m2.begin()->first << std::endl;
	// m.erase(m.begin());
	return (0);
}
