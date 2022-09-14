#include "../../containers/vector.hpp"
#include <iostream>

int main()
{
	ft::vector<int> v(5, 2);
	ft::vector<int>::iterator it;


	// std::cout << std::endl << "#====== push back end =====#" << std::endl;
	for (int i = 0; i < 5; i++)
		v[i] = i;

	std::cout << std::endl << "#====== begin end =====#" << std::endl;
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
	std::cout << std::endl;
	
	std::cout << std::endl << "#====== iterator pointer =====#" << std::endl;
	int k = 1;
	ft::vector<int>::iterator::pointer p = &k;
	std::cout << *p << std::endl;

	std::cout << std::endl << "#===== rit =====#" << std::endl;
	ft::vector<int>::reverse_iterator rit;
	for (rit = v4.rbegin(); rit != v4.rend(); rit++)
		std::cout << *rit << " ";
	std::cout << std::endl;

	// std::cout << std::endl << "#===== front back =====#" << std::endl;
	// ft::vector<int> vempty;
	// std::cout << vempty.front() << std::endl;
	// std::cout << vempty.back() << std::endl;

	std::cout << std::endl << "#===== assign =====#" << std::endl;
	v4.assign(v3.begin(), v3.end());
	for (rit = v4.rbegin(); rit != v4.rend(); rit++)
		std::cout << *rit << " ";
	std::cout << std::endl;

	std::cout << std::endl << "#===== max_size =====#" << std::endl;
	ft::vector<int> iv;
	ft::vector<char> cv;
	std::cout << iv.max_size() << "\n" << cv.max_size() << std::endl;

	// std::cout << std::endl << "#===== reserve =====#" << std::endl;
	// ft::vector<int> v5;
	// v5.reserve(v5.max_size() + 1);
	// std::cout << v5.size() << std::endl;

	std::cout << std::endl << "#===== resize =====#" << std::endl;
	std::cout << v.capacity() << std::endl;
	v.resize(5);
	std::cout << v.capacity() << " " << v.size() << " " << v.at(4) << std::endl;
	v.resize(30);
	std::cout << v.capacity() << " " << v.size() << " " << v.at(29) << std::endl;

}
