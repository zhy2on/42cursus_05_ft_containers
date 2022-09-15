#include <vector>
#include <iostream>
#include <iterator>

int main()
{
	std::vector<int> v(5, 2);
	std::vector<int>::iterator it;

	// std::cout << std::endl << "#====== push back end =====#" << std::endl;
	for (int i = 0; i < 5; i++)
		v[i] = i;

	std::cout << std::endl
			  << "#====== constructor, begin end =====#" << std::endl;
	for (it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::vector<int> v2(v.begin(), v.end());
	for (it = v2.begin(); it != v2.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::vector<int> v3(v2);
	for (it = v3.begin(); it != v3.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::vector<int> v4(7, 7);
	v4 = v2;
	for (it = v4.begin(); it != v4.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << std::endl
			  << "#===== reverse iterator =====#" << std::endl;
	std::vector<int>::reverse_iterator rit;
	for (rit = v4.rbegin(); rit != v4.rend(); rit++)
		std::cout << *rit << " ";
	std::cout << std::endl;

	// std::cout << std::endl << "#===== front back =====#" << std::endl;
	// std::vector<int> vempty;
	// std::cout << vempty.front() << std::endl;
	// std::cout << vempty.back() << std::endl;

	std::cout << std::endl
			  << "#===== assign =====#" << std::endl;
	v3.resize(30);
	v4.assign(v3.begin(), v3.end());
	for (rit = v4.rbegin(); rit != v4.rend(); rit++)
		std::cout << *rit << " ";
	std::cout << std::endl;

	std::cout << std::endl
			  << "#===== max_size =====#" << std::endl;
	std::vector<int> iv;
	std::vector<char> cv;
	std::cout << iv.max_size() << "\n"
			  << cv.max_size() << std::endl;

	// std::cout << std::endl << "#===== reserve =====#" << std::endl;
	// std::vector<int> v5;
	// v5.reserve(v5.max_size() + 1);
	// std::cout << v5.size() << std::endl;

	std::cout << std::endl
			  << "#===== resize =====#" << std::endl;
	std::cout << v.capacity() << std::endl;
	v.resize(30, 100);
	std::cout << v.capacity() << " " << v.size() << " " << v.at(29) << std::endl;
	v.resize(5, 100);
	std::cout << v.capacity() << " " << v.size() << " " << v.at(4) << std::endl;
	for (int i = 0; i < 5; i++)
	{
		v.resize(60 + i);
		std::cout << "capacity: " << v.capacity() << std::endl;
	}

	std::cout << std::endl
			  << "#===== push_back =====#" << std::endl;
	v.resize(0);
	v.push_back(11);
	v.push_back(22);
	v.push_back(33);
	for (int i = 0; i < v.size(); i++)
		std::cout << v.at(i) << " ";
	std::cout << std::endl;

	std::cout << std::endl
			  << "#===== pop_back =====#" << std::endl;
	v.resize(1);
	std::cout << v.size() << std::endl;
	v.pop_back();
	std::cout << v.size() << std::endl;
	// v.pop_back();

	std::cout << std::endl
			  << "#===== insert =====#" << std::endl;
	v.resize(3, 100);
	v.insert(v.begin(), 200);
	std::cout << "insert value: " << *it << std::endl;
	for (int i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;
	v.insert(v.begin(), 2, 300);
	for (int i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;

	std::cout << std::endl
			  << "#===== erase =====#" << std::endl;
	// v.erase(v.begin() + v.size() + 1);
	for (int i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;
	v.erase(v.begin() + 2);
	for (int i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;
	v.erase(v.begin() + 1, v.begin() + 3);
	for (int i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;

	std::cout << std::endl
			  << "#===== swap =====#" << std::endl;
	v.resize(10, 2);
    v2.resize(5, 1);
    std::cout << &v2 << std::endl;
    std::cout << v2.size() << " " << v2.capacity() << std::endl;
    for (int i = 0; i < v2.size(); i++)
        std::cout << v2[i] << " ";
    std::cout << std::endl;
    v.swap(v2);
    std::cout << &v2 << std::endl;
    std::cout << v2.size() << " " << v2.capacity() << std::endl;
    for (int i = 0; i < v2.size(); i++)
        std::cout << v2[i] << " ";
    std::cout << std::endl;

	std::cout << std::endl
			  << "#===== swap =====#" << std::endl;
	v.clear();
	std::cout << v.size() << " " << v.capacity() << std::endl;

	std::cout << std::endl
			  << "#===== get_allocator =====#" << std::endl;
	int *p;
	p = v.get_allocator().allocate(5);
	for (int i = 0; i < 5; i++)
		v.get_allocator().construct(&p[i], i);
	std::cout << "The allocated array contains:";
	for (int i = 0; i < 5; i++)
		std::cout << ' ' << p[i];
	std::cout << std::endl;

	system("leaks std-vector");
}
