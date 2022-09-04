#include <iostream>
#include <vector>

int main()
{
	std::vector<int> v(5, 3);
	std::vector<int>::iterator it;

	for (it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
}