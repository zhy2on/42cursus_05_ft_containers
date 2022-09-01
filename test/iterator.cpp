#include <iostream>
#include <vector>
#include "../containers/vector_iterator.hpp"

int main()
{
	std::vector<const int> v;
	std::vector<int> v2;
	int a = 1;

	ft::vector_iterator<const int> it;
	ft::vector_iterator<int> it2;

	it = &a;	

}