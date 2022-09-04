#include <iostream>

namespace ft {

	template <class Category, class T, class Distance = std::ptrdiff_t,
			  class Pointer = T *, class Reference = T &>
	struct Base
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};
}

struct Child : public ft::Base<int, int>
{
	pointer a;
private:
	pointer b;
};

int main()
{
	Child child;
	int k = 3;

	child.a = &k;
	std::cout << *child.a << std::endl;
}