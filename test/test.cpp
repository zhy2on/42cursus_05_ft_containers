#include <iostream>

int main()
{
	int i;
	for (i = 10; i >= 0; --i)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	std::cout << i << std::endl;
	for (i = 10; i >= 0; i--)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	std::cout << i << std::endl;
}