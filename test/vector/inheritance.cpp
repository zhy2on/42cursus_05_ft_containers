#include <iostream>
#include "test2.hpp"


int main()
{
	ft::Child<int> child;
	int k = 3;

	child.a = &k;
	std::cout << *child.a << std::endl;
}