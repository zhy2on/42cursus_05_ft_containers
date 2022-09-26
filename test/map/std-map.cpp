#include <iostream>
#include <map>

int main()
{
	std::map<char, int> m;

	m.insert(std::make_pair('a', 1));

	std::cout << m.find('a')->first << std::endl;
	return (0);
}
