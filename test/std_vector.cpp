#include <iostream>
#include <vector>

int main()
{
	std::vector<int> v(5, 2);

	std::cout << v.capacity() << std::endl;

	v.reserve(v.max_size() - 10);

	std::cout << v.capacity() << std::endl;
}